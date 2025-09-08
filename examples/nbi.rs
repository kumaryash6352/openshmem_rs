use std::error::Error;

use openshmem_rs::ShmemCtx;
use rand::random;

// NBI operations let us perform PGAS operations
// asynchronously--or more often, concurrently.

fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let shmalloc = ctx.shmallocator();
    let pe0 = ctx.pe(0);

    // generate some random data to pull from
    let haystack = shmalloc.array_gen(|_| random::<f32>(), 256);
    // some data points we're interested in
    let interesting_idxs = [0, 2, 42, 34, 35];
    let mut gets = Vec::with_capacity(interesting_idxs.len());

    for idx in interesting_idxs {
        // no waiting on communication here,
        // we got a loop to loop
        gets.push(pe0.get_single_nbi(&haystack, idx));
    }

    // instead, comms are deferred until the 'quiet'.
    // you can quiet a whole vec at once
    let _interesting_data = ctx.quiet(gets);
    // or a tuple if you know how many you want
    let (_twenty, _twentyfour) = ctx.quiet((
        pe0.get_single_nbi(&haystack, 20),
        pe0.get_single_nbi(&haystack, 24),
    ));

    Ok(())
}
