use std::error::Error;

use openshmem_rs::{atomics::Atomic, ShmemCtx, PE};
use rand::{thread_rng, Rng as _};

/// Monte-carlo estimation of pi.
///
/// Probably would be more efficient to,
/// instead of using an atomic, having
/// each PE maintain it's own count of hits,
/// but this serves as a decent example of the
/// atomic API.

fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let shmalloc = ctx.shmallocator();
    let mut rng = thread_rng();

    let hit = shmalloc.shbox(Atomic::new(0usize));
    let tries_per_pe = 2_000_000;

    for _ in 0..tries_per_pe {
        let (x, y): (f32, f32) = rng.gen();
        if x.powi(2) + y.powi(2) <= 1.0 {
            hit.atomic_inc(PE(0), &ctx);
        }
    }
    ctx.barrier_all();

    if ctx.my_pe() == 0 {
        let percent_hit =
            hit.atomic_fetch_local(&ctx) as f32
            / (tries_per_pe as f32 * ctx.n_pes() as f32);
        dbg!(percent_hit);
        println!("estimated value of pi: {}",
            4. * percent_hit);
    }

    Ok(())
}
