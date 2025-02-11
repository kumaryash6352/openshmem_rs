use std::{error::Error, fs::File, io::Read};

use openshmem_rs::ShmemCtx;

fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let my_pe = ctx.my_pe();

    let shmallocator = ctx.shmallocator();

    // obtain 4 random ints
    let mut randoms = [0; 4];
    let mut urand = File::open("/dev/urandom")?;
    urand.read_exact(&mut randoms)?;
    drop(urand); // no need to keep it around

    // convert to 4 random floats
    let mut numbers = shmallocator
        .array_gen(|i| randoms[i] as f32 / u8::MAX as f32, 4);

    // also select the largest float
    let mut max = shmallocator
        .shbox(*numbers.iter().max_by(|a, b| a.total_cmp(b)).unwrap());
    println!("[PE {my_pe}]: grabbed {:.2?} from urandom (max = {:.2})", &numbers[..], *max);

    ctx.barrier_all();
    numbers.reduce_min(&ctx);
    max.reduce_max(&ctx);
    println!("[PE {my_pe}]: after min reduction seeing {:.2?} (max = {:.2})", &numbers[..], *max);

    Ok(())
}
