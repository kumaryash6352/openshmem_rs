use openshmem_rs::{atomics::Atomic, ShmemCtx, PE};



fn main() -> Result<(), Box<dyn std::error::Error>> {
    let ctx = ShmemCtx::init()?;
    let shmalloc = ctx.shmallocator();
    let int = shmalloc.shbox(Atomic::new(0usize));

    if ctx.my_pe() == 0 {
        println!("hammering counter with 20 simultaneous increments");
    }
    ctx.barrier_all();

    for _ in 0..20 {
        int.atomic_inc(PE(0), &ctx);
    }

    ctx.barrier_all();

    if ctx.my_pe() == 0 {
        println!("expecting counter to equal npes * 20 ({})", ctx.n_pes() * 20);
        assert_eq!(int.atomic_fetch_local(&ctx), ctx.n_pes() * 20, "counter mismatch!");
        println!("counter valid!");
    }

    Ok(())
}
