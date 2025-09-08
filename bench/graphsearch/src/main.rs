use openshmem_matrix::CrsMatrix;
use openshmem_rs::{
    atomics::Atomic, shmalloc::{Shbox, Shmallocator}, ShmemCtx
};
use openshmem_vec::Shvec;
use rayon::prelude::*;
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
    let mut search_cursor = shm.shbox(Atomic::new(0usize));
    println!("[PE {:>2}] parsed {} searchpairs", mype, all_searches.len());
    let mut distances = Vec::with_capacity(all_searches.len());
    println!("[PE {:>2}] starting searches!", mype);
    for (from, to) in all_searches {
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
            searches.len(),
            start.elapsed().as_secs_f32(),
            searches.len() as f32 / start.elapsed().as_secs_f32()
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
    let mpe = ctx.my_pe().raw();
    // strategy: remote read all elements from connects to
    //           we recurse into all connected nodes where idx % n_pes == mpe
    //           at each step, if a node has found the element we want, we send the signal.
    //           if the signal, we exit and that node shares the path with all others
    // TODO: new strat:
    //           global atomic counter
    //           each pe fetchincs the atomic counter
    //           runs the fetchinc'd idx search pair
    //           "work stealing"
    let conn_buf = if adj.row_on_this_pe(from) {
        let conns = adj.cols_on_row(from);
        Shvec::from_iter(ctx, shm, conns.as_ref().into_iter().copied())
    } else {
        Shvec::from_iter(ctx, shm, [])
    };
    let first_conns = conn_buf.collect();
    // println!("pe {}: first_conns = {first_conns:?}", mpe);
    let mut len = shm.shbox(0);
    // divide work
    let mut my_targets = (*first_conns)
        .into_iter()
        .skip(mpe)
        .step_by(ctx.n_pes())
        .copied()
        .collect::<Vec<_>>();
    // "feels right" heuristic
    // if my_targets.len() > 32767 {
    //     my_targets.par_sort_unstable();
    // } else {
    // screw the heuristic we use par elsewhere too
    my_targets.sort_unstable();
    // }
    let mut q1 = my_targets.clone();
    let mut q2 = my_targets;
    let mut flag = shm.shbox(0);
    // println!("pe {}: start search for {to}...", ctx.my_pe().raw());
    if mpe == 0 {
        // TODO: update progress
        // println!("start search for {to}");
    }
    *len = bfs_p(ctx, shm, &adj, to, &mut q1, &mut q2, &mut flag, 1);
    ctx.barrier_all();
    if mpe == 0 {
        // println!("found {from}..[{} nodes]..to", *len - 1);
    }

    len.reduce_min(ctx);
    *len
}

fn bfs_p(
    ctx: &ShmemCtx,
    shm: &Shmallocator<'_>,
    adj: &CrsMatrix<'_, u8>,
    target: usize,
    q_targets: &mut Vec<usize>,
    q_scratch: &mut Vec<usize>,
    flag: &mut Shbox<'_, usize>,
    layers: usize,
) -> usize {
    if q_targets.binary_search(&target).is_ok() {
        // println!(
        //     "halting: i (pe {}) found a path in {layers}",
        //     ctx.my_pe().raw()
        // );
        **flag = ctx.my_pe().raw() + 1;
    }
    //println!("pe {}: waiting on flag max...", ctx.my_pe().raw());
    flag.reduce_max(ctx);
    if **flag > 0 {
        // println!("halting: pe {} found a path", **flag);
        layers
    } else {
        // println!(
        //     "pe {}: no pe has found target yet. recursing, q = {q:?}",
        //     ctx.my_pe().raw()
        // );
        // prepare new queue
        let next_targets = q_targets
            .iter()
            .map(|idx| adj.cols_on_row(*idx))
            .collect::<Vec<_>>();
        q_scratch.clear();
        for t in next_targets {
            q_scratch.extend_from_slice(&t);
        }
        q_scratch.par_sort_unstable();
        q_scratch.dedup();
        if layers > 200 || q_scratch == q_targets {
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
            flag,
            layers + 1,
        )
    }
}

fn parse_edge<'a>(line: &'a str) -> Option<(usize, usize)> {
    let (a, b) = line.split_once(",")?;
    a.parse().ok().zip(b.parse().ok())
}
