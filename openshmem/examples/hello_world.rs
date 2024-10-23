use openshmem::ShmemCtx;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let ctx = ShmemCtx::init()?;

    let my_pe = ctx.my_pe().raw();

    println!("Hello from PE {my_pe}!");

    ctx.barrier_all();
    let shmallocator = ctx.shmallocator();
    // implicit barrier (shmalign)
    let mut shared = shmallocator.array::<f32>(0.0, 8);
    ctx.barrier_all();

    #[cfg(feature = "rma")]
    if my_pe == 0 {
        // mutate PE(1)'s shared
        ctx.pe(1).get(&mut shared, |arr| {
            *arr[0] = 1.0;
        });
    } else if my_pe == 1 {
        // mutate PE(0)'s shared
        ctx.pe(0).get(&mut shared, |arr| {
            *arr[0] = 2.0;
        });
    }
    #[cfg(not(feature = "rma"))]
    if my_pe == 0 {
        let mut remote = ctx.pe(1).view_mut(&mut shared, 4..8);
        for i in &mut remote[0..4] {
            *i = 1.0;
        }
        // remote is dropped at the end of this scope,
        // copying its local buffer to the remote host.
    } else if my_pe == 1 {
        let mut remote = ctx.pe(0).view_mut(&mut shared, 0..4);
        for i in &mut remote[0..4] {
            *i = 2.0;
        }
        // remote is dropped at the end of this scope,
        // copying its local buffer to the remote host.
    }

    ctx.barrier_all();

    println!("pe {my_pe} sees {shared:?}");

    // any access to sharray after we drop the ctx
    // is a compile-time error.

    Ok(())
}