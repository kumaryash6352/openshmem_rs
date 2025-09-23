use openshmem_matrix::CrsMatrix;
use openshmem_rs::{
    atomics::Atomic, shmalloc::{Shbox, Shmallocator}, ShmemCtx
};
use openshmem_vec::Shvec;
use rayon::prelude::*;
use rustc_hash::FxHashSet;
use std::{
    error::Error,
    fs::File,
    io::{BufRead as _, BufReader, Write},
    time::Instant,
};

fn main() -> Result<(), Box<dyn Error>> {
    println!("Hello, world!");

    let ctx = ShmemCtx::init().unwrap();
    let start = Instant::now();
    let shm = ctx.shmallocator();
    let npes = ctx.n_pes();
    let mype = ctx.my_pe().raw();

    println!("[PE {:>2}] start reading edgelist", mype);
    let input = BufReader::new(File::open("edgelist")?)
        .lines()
        .collect::<Result<Vec<String>, std::io::Error>>()?;
    let elines_per_pe = input.len().div_ceil(npes);
    println!("[PE {:>2}] read edgelist", mype);

    println!("[PE {:>2}] start parse edgelist", mype);
    let edges = input
        .par_iter()
        .skip(mype * elines_per_pe)
        .take(elines_per_pe)
        .filter_map(|s| parse_edge(&s))
        .collect::<Vec<_>>();
    // let edges = Shvec::from_iter(&ctx, &shm, edges);
    println!(
        "[PE {:>2}] parsed {} edges from edgelist",
        mype,
        edges.len()
    );
    let mut max = shm.shbox(
        edges
            .par_iter()
            .map(|(r, c)| r.max(c))
            .max()
            .copied()
            .expect("at least one edge"),
    );
    max.reduce_max(&ctx);
    if mype == 0 {
        println!("[PE {:>2}] adj matrix dimensions: {}x{}", mype, *max, *max);
    }

    println!(
        "[PE {:>2}] storing {} edges into adj matrix",
        mype,
        edges.len()
    );
    let edges = edges
        .into_par_iter()
        .map(|(r, c)| (r, c, 1u8))
        .collect::<Vec<_>>();
    let adj = CrsMatrix::from_coo(*max + 1, *max + 1, &edges, &ctx, &shm);

    println!("[PE {:>2}] global edges: {}", mype, adj.nnz());

    println!("[PE {:>2}] parsing searchlist...", mype);
    let search_input = BufReader::new(File::open("searchlist")?)
        .lines()
        .collect::<Result<Vec<String>, std::io::Error>>()?;
    let slines_per_pe = search_input.len().div_ceil(npes);
    let searches = search_input
        .par_iter()
        .skip(mype * slines_per_pe)
        .take(slines_per_pe)
        .filter_map(|s| parse_edge(&s))
        .collect::<Vec<_>>();
    let searches = Shvec::from_iter(&ctx, &shm, searches.into_iter());
    let all_searches = searches.collect();
    println!("[PE {:>2}] parsed {} searchpairs", mype, all_searches.len());
    let mut distances = Vec::with_capacity(all_searches.len());
    println!("[PE {:>2}] starting searches!", mype);
    for (from, to) in searches.iter() {
        println!("[PE {mype:>2}]search #{:>4}: {from:>10} -> {to:>10}...", distances.len());
        distances.push(bfs(from, to, &adj, &ctx, &shm));
    }

    if mype == 0 {
        println!("max distance: {}", distances.iter().max().unwrap());
        println!("min distance: {}", distances.iter().min().unwrap());
        println!(
            "avg distance: {}",
            distances.iter().sum::<usize>() as f32 / distances.len() as f32
        );
        let mut out = File::create("searchtime")?;
        writeln!(
            out,
            "{} searches in {}s ({} searches per second)",
            all_searches.len(),
            start.elapsed().as_secs_f32(),
            all_searches.len() as f32 / start.elapsed().as_secs_f32()
        )?;
    }

    Ok(())
}
fn bfs(
    from: usize,
    to: usize,
    adj: &CrsMatrix<'_, u8>,
    ctx: &ShmemCtx,
    shm: &Shmallocator<'_>,
) -> usize {
    let mut conns = adj.cols_on_row(from).iter().copied().collect::<Vec<_>>();
    let mut q2 = Vec::with_capacity(conns.len());
    bfs_p(ctx, shm, &adj, to, &mut conns, &mut q2, &mut FxHashSet::default(), 1)
}

fn bfs_p(
    ctx: &ShmemCtx,
    shm: &Shmallocator<'_>,
    adj: &CrsMatrix<'_, u8>,
    target: usize,
    q_targets: &mut Vec<usize>,
    q_scratch: &mut Vec<usize>,
    seen: &mut FxHashSet<usize>,
    layers: usize,
) -> usize {
    if q_targets.binary_search(&target).is_ok() {
        layers
    } else {
        q_scratch.clear();
        q_scratch.extend(q_targets.iter().map(|i| adj.cols_on_row(*i)).flatten());
        q_scratch.par_sort_unstable();

        // prepare new queue
        let next_targets = q_targets
            .iter()
            .map(|idx| adj.cols_on_row(*idx))
            .flatten()
            .filter(|i| !seen.contains(i))
            .collect::<Vec<_>>();
        q_scratch.clear();
        q_scratch.extend(next_targets);
        q_scratch.par_sort_unstable();
        q_scratch.dedup();
        q_scratch.iter().for_each(|i| { seen.insert(*i); });
        if layers > 20000 || q_scratch == q_targets {
            println!(
                "pe {}: i think i'm in an infinite loop: {q_targets:?}",
                ctx.my_pe()
            );
        }
        bfs_p(
            ctx,
            shm,
            adj,
            target,
            q_scratch,
            q_targets,
            seen,
            layers + 1,
        )
    }
}

fn parse_edge<'a>(line: &'a str) -> Option<(usize, usize)> {
    let (a, b) = line.split_once(",")?;
    a.parse().ok().zip(b.parse().ok())
}
