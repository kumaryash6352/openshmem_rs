use std::error::Error;

use openshmem::ShmemCtx;



fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let npes = ctx.n_pes();
    let is_root = ctx.my_pe().raw() == 0;
    let shmallocator = ctx.shmallocator();
    if npes == 1 {
        println!("this example is meaningless with only 1 pe");
        return Ok(())
    }

    let shbox = shmallocator.array(0, npes - 1);

    if is_root {

    }

    Ok(())
}
