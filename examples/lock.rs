use std::{error::Error, fs::File, io::Read, thread::sleep, time::Duration};

use openshmem_rs::{shmutex::Shmlock, ShmemCtx};

fn rand(rng: &mut usize) -> f32 {
    const A: usize = 75;
    const C: usize = 74;
    *rng = (A * *rng + C) % u32::MAX as usize;
    *rng as f32/ u32::MAX as f32
}

fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let shmallocator = ctx.shmallocator();
    let stdout = Shmlock::new(&shmallocator);
    let my_pe = ctx.my_pe().raw();
    let mut rng = 0xDEADBEEF;

    if my_pe == 0 {
        println!("unlocked prints:");
    }
    ctx.barrier_all();
    for _ in 0..20 {
        sleep(Duration::from_secs_f32(0.01 + rand(&mut rng) * 0.005));
        print!("{my_pe}");
    }
    ctx.barrier_all();
    if my_pe == 0 {
        println!("\nlocked prints:");
    }
    ctx.barrier_all();
    let lock = stdout.lock();
    for _ in 0..20 {
        // vary per iter by 5-15 ms
        sleep(Duration::from_secs_f32(0.01 + rand(&mut rng) * 0.01 - 0.005));
        print!("{my_pe}");
    }
    println!();
    drop(lock); // locks are dropped at end of scope too

    Ok(())
}
