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
        println!(
            "expecting counter to equal npes * 20 ({})",
            ctx.n_pes() * 20
        );

        // all accesses are guarded by atomic ops
        // won't compile \/
        // println!("{}", *int);
        assert_eq!(
            int.atomic_fetch_local(&ctx),
            ctx.n_pes() * 20,
            "counter mismatch!"
        );
        println!("counter valid!");
    }

    // you can also apply atomic operations to a list of things
    let xs = shmalloc.array_gen(|_| Atomic::new(0usize), 20);
    for _ in 0..20 {
        xs.slice(0..20)
            .iter()
            .for_each(|a| a.atomic_inc(PE(0), &ctx));
    }
    ctx.barrier_all();

    if ctx.my_pe() == 0 {
        println!(
            "expecting all counters to equal npes * 20 ({})",
            ctx.n_pes() * 20
        );
        for x in xs.slice(0..20).iter() {
            assert_eq!(x.atomic_fetch_local(&ctx), ctx.n_pes() * 20);
        }
        println!(
            "counters are valid!",
        );
    }

    // or a single thing in a list of things
    for _ in 0..20 {
        xs.slice(0).atomic_inc(PE(0), &ctx);
    }
    ctx.barrier_all();

    if ctx.my_pe() == 0 {
        println!(
            "expecting counters[0] to equal npes * 40 ({})",
            ctx.n_pes() * 40
        );

        assert_eq!(xs.slice(0).atomic_fetch_local(&ctx), ctx.n_pes() * 40);
        println!(
            "counters[0] is valid!",
        );
    }

    Ok(())
}
