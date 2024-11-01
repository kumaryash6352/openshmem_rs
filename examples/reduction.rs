use std::{error::Error, fs::File, io::Read};

use openshmem::ShmemCtx;

fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let my_pe = ctx.my_pe();

    let shmallocator = ctx.shmallocator();

    let mut randoms = [0; 4];
    let mut urand = File::open("/dev/urandom")?;
    urand.read_exact(&mut randoms)?;
    drop(urand); // no need to keep it around

    let mut numbers = shmallocator.array_gen(|i| randoms[i] as f32 / u8::MAX as f32, 4);
    let mut max = shmallocator.shbox(*numbers.iter().max_by(|a, b| a.total_cmp(b)).unwrap());
    println!("[PE {my_pe}]: grabbed {:.2?} from urandom (max = {:.2})", &numbers[..], *max);

    ctx.barrier_all();
    numbers.reduce_min(numbers.len(), &ctx);
    max.reduce_max(&ctx);
    println!("[PE {my_pe}]: after min reduction seeing {:.2?} (max = {:.2})", &numbers[..], *max);

    Ok(())
}
