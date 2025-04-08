use openshmem_matrix::CrsMatrix;
use openshmem_rs::{
    shmalloc::{Shbox, Shmallocator},
    ShmemCtx,
};
use openshmem_vec::Shvec;
use rayon::prelude::*;
use std::{
    error::Error,
    fs::File,
    io::{BufRead as _, BufReader},
};

fn main() -> Result<(), Box<dyn Error>> {
    println!("Hello, world!");

    let ctx = ShmemCtx::init().unwrap();
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
    let mut adj = CrsMatrix::new(*max + 1, *max + 1, &ctx, &shm);

    println!("[PE {:>2}] storing edges into adj matrix", mype);
    let edges = edges
        .into_par_iter()
        .map(|(r, c)| (r, c, 1u8))
        .collect::<Vec<_>>();
    for (i, chunk) in edges.chunks(262144).enumerate() {
        println!(
            "[PE {:>2}] storing edges[{}..{}] into adj matrix",
            mype,
            i * 262144,
            (i + 1) * 262144
        );
        adj.put_many_all(&chunk);
    }
    println!("[PE {:>2}] global edges: {}", mype, adj.nnz());

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
    let mut distances = Vec::new();
    println!("{:?}", all_searches);

    for (from, to) in all_searches {
        distances.push(bfs(from, to, &adj, &ctx, &shm));
    }

    println!("max distance: {}", distances.iter().max().unwrap());
    println!("min distance: {}", distances.iter().min().unwrap());
    println!("avg distance: {}", distances.iter().sum::<usize>() as f32 / distances.len() as f32);

    drop(searches);

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
    // fn bfs_p(
    //     from: usize,
    //     to: usize,
    //     adj: &CrsMatrix<'_, u8>,
    //     npes: usize,
    //     ctx: &ShmemCtx,
    //     n_conns_buf: &mut Shbox<'_, usize>,
    //     conns_buf: &mut Shvec<'_, usize>,
    //     path: &mut Vec<usize>,
    // ) {
    //     conns_buf.clear();
    //     if adj.row_on_this_pe(from) {
    //         // my job to fill conns_buf
    //         let tos = adj.cols_on_row(from).expect("all paths must be findable");
    //         conns_buf.extend(tos);
    //     } else {
    //         conns_buf.grow_to(0); // let the ndoe with the cols figure out length
    //     }
    //     ctx.barrier_all();

    //     conns_buf.collect();

    // }
    // strategy: remote read all elements from connects to
    //           we recurse into all connected nodes where idx % n_pes == mpe
    //           at each step, if a node has found the element we want, we send the signal.
    //           if the signal, we exit and that node shares the path with all others
    let conn_buf = if adj.row_on_this_pe(from) {
        let conns = adj.cols_on_row(from).expect("all paths are findable");
        Shvec::from_iter(ctx, shm, conns.into_iter().copied())
    } else {
        Shvec::from_iter(ctx, shm, [])
    };
    let first_conns = conn_buf.collect();
    let mut len = shm.shbox(0);
    // divide work
    let my_targets = (*first_conns)
        .into_iter()
        .skip(mpe)
        .step_by(ctx.n_pes())
        .copied()
        .collect::<Vec<_>>();
    let mut q = my_targets;
    let mut flag = shm.shbox(0);
    bfs_p(ctx, shm, &adj, to, &mut q, &mut flag, 0);

    len.reduce_max(ctx);
    *len
}

fn bfs_p(
    ctx: &ShmemCtx,
    shm: &Shmallocator<'_>,
    adj: &CrsMatrix<'_, u8>,
    target: usize,
    q: &mut Vec<usize>,
    flag: &mut Shbox<'_, usize>,
    layers: usize,
) -> usize {
    if q.contains(&target) {
        println!("halting: i found a path in {layers}");
        **flag = ctx.my_pe().raw();
        flag.reduce_max(ctx);
        layers
    } else {
        flag.reduce_max(ctx);
        if **flag > 0 {
            println!("halting: pe {} found a path", **flag);
            layers
        } else {
            // prepare new queue
            let next_targets = q.iter().map(|idx| {
                adj.cols_on_row_remote(*idx)
            }).collect::<Vec<_>>();
            q.clear();
            for t in next_targets {
                q.extend_from_slice(&t);
            }
            bfs_p(ctx, shm, adj, target, q, flag, layers + 1)
        }
    }
}

fn parse_edge<'a>(line: &'a str) -> Option<(usize, usize)> {
    let (a, b) = line.split_once(",")?;
    a.parse().ok().zip(b.parse().ok())
}
