use openshmem_matrix::CrsMatrix;
use openshmem_rs::{
    atomics::Atomic, shmalloc::{Shbox, Shmallocator}, ShmemCtx
};
use openshmem_vec::Shvec;
use rayon::prelude::*;
use rustc_hash::FxHashSet;
use std::{
    env,
    error::Error,
    fs::File,
    io::{BufRead as _, BufReader, Write},
    time::Instant,
};

fn main() -> Result<(), Box<dyn Error>> {
    eprintln!("Hello, world!");

    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("Usage: {} <searchlist> <edgelist>", args[0]);
        std::process::exit(1);
    }
    let searchlist_path = &args[1];
    let edgelist_path = &args[2];

    let ctx = ShmemCtx::init().unwrap();
    let start = Instant::now();
    let shm = ctx.shmallocator();
    let npes = ctx.n_pes();
    let mype = ctx.my_pe().raw();

    eprintln!("[PE {:>2}] start reading edgelist", mype);
    let input = BufReader::new(File::open(edgelist_path)?)
        .lines()
        .collect::<Result<Vec<String>, std::io::Error>>()?;
    let elines_per_pe = input.len().div_ceil(npes);
    eprintln!("[PE {:>2}] read edgelist", mype);

    eprintln!("[PE {:>2}] start parse edgelist", mype);
    let edges = input
        .iter()
        .skip(mype * elines_per_pe)
        .take(elines_per_pe)
        .filter_map(|s| parse_edge(&s))
        .collect::<Vec<_>>();
    // let edges = Shvec::from_iter(&ctx, &shm, edges);
    eprintln!(
        "[PE {:>2}] parsed {} edges from edgelist",
        mype,
        edges.len()
    );
    let mut max = shm.shbox(
        edges
            .iter()
            .map(|(r, c)| r.max(c))
            .max()
            .copied()
            .expect("at least one edge"),
    );
    max.reduce_max(&ctx);
    if mype == 0 {
        eprintln!("[PE {:>2}] adj matrix dimensions: {}x{}", mype, *max, *max);
    }

    eprintln!(
        "[PE {:>2}] storing {} edges into adj matrix",
        mype,
        edges.len()
    );
    let edges = edges
        .into_iter()
        .map(|(r, c)| (r, c, 1u8))
        .collect::<Vec<_>>();
    let adj = CrsMatrix::from_coo(*max + 1, *max + 1, &edges, &ctx, &shm);

    eprintln!("[PE {:>2}] global edges: {}", mype, adj.nnz());

    eprintln!("[PE {:>2}] parsing searchlist...", mype);
    let search_input = BufReader::new(File::open(searchlist_path)?)
        .lines()
        .collect::<Result<Vec<String>, std::io::Error>>()?;
    let slines_per_pe = search_input.len().div_ceil(npes);
    let searches = search_input
        .iter()
        .skip(mype * slines_per_pe)
        .take(slines_per_pe)
        .filter_map(|s| parse_edge(&s))
        .collect::<Vec<_>>();
    let searches = Shvec::from_iter(&ctx, &shm, searches.into_iter());
    let all_searches = searches.collect();
    eprintln!("[PE {:>2}] parsed {} searchpairs", mype, all_searches.len());
    let mut distances = Vec::with_capacity(all_searches.len());
    eprintln!("[PE {:>2}] starting searches!", mype);
    for (from, to) in searches.iter() {
        eprintln!("[PE {mype:>2}]search #{:>4}: {from:>10} -> {to:>10}...", distances.len());
        distances.push(bfs(from, to, &adj, &ctx, &shm));
    }

    ctx.barrier_all();
    
    if mype == 0 {
        eprintln!("max distance: {}", distances.iter().max().unwrap());
        eprintln!("min distance: {}", distances.iter().min().unwrap());
        eprintln!(
            "avg distance: {}",
            distances.iter().sum::<usize>() as f32 / distances.len() as f32
        );
        let searches_per_second = all_searches.len() as f32 / start.elapsed().as_secs_f32();
        let mut out = File::create("searchtime")?;
        writeln!(
            out,
            "{} searches in {}s ({} searches per second)",
            all_searches.len(),
            start.elapsed().as_secs_f32(),
            searches_per_second
        )?;
        println!("{}", searches_per_second);
    }

    Ok(())
}
fn bfs(
    from: usize,
    to: usize,
    adj: &CrsMatrix<'_, u8>,
    ctx: &ShmemCtx,
    _shm: &Shmallocator<'_>,
) -> usize {
    if from == to {
        return 0;
    }
    
    // prealloc
    let mut q_targets = Vec::with_capacity(256);
    let mut q_scratch = Vec::with_capacity(256);
    let mut seen = FxHashSet::with_capacity_and_hasher(65536, Default::default());

    // initial level
    let neighbors = adj.cols_on_row(from);
    q_targets.extend(neighbors.iter().copied());
    sort_and_dedup(&mut q_targets);
    
    let mut layers = 1;
    
    while !q_targets.is_empty() && layers <= 20000 {
        if q_targets.binary_search(&to).is_ok() {
            return layers;
        }
        
        q_scratch.clear();
        for &node in &q_targets {
            let node_neighbors = adj.cols_on_row(node);
            for neighbor in node_neighbors {
                if !seen.contains(&neighbor) {
                    q_scratch.push(neighbor);
                }
            }
        }
        
        for &node in &q_targets {
            seen.insert(node);
        }
        
        sort_and_dedup(&mut q_scratch);
        
        // anti infinite loop
        if layers > 20000 || (q_scratch.len() == q_targets.len() && q_scratch == q_targets) {
            eprintln!(
                "pe {}: BFS infinite loop detected at layer {}",
                ctx.my_pe().raw(),
                layers
            );
            break;
        }
        
        std::mem::swap(&mut q_targets, &mut q_scratch);
        layers += 1;
    }
    
    usize::MAX
}

fn sort_and_dedup(vec: &mut Vec<usize>) {
    if vec.len() <= 1 {
        return;
    }
    
    vec.sort_unstable();
    vec.dedup();
}

fn parse_edge<'a>(line: &'a str) -> Option<(usize, usize)> {
    let (a, b) = line.split_once(",")?;
    a.parse().ok().zip(b.parse().ok())
}
