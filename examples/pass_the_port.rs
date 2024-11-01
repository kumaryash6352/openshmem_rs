use openshmem_rs::ShmemCtx;
use std::error::Error;

/// Example from paper.

fn main()
  -> Result<(), Box<dyn Error>>
{
  // Initialize the OpenSHMEM library,
  // resulting in a ShmemCtx.
  let ctx = ShmemCtx::init()?;

  // Get my PE index as an integer
  // instead of a PE structure.
  let my_pe = ctx.my_pe().raw();
  let npes = ctx.n_pes();
  println!("Hello from PE {my_pe}!");

  ctx.barrier_all();

  // Obtain a reference to the
  // Shmallocator,  which handles
  // symmetric heap allocations.
  let shmallocator = ctx.shmallocator();
  // Allocate a slice of 8 f32 floats
  // on the symmetric heap.
  let mut shared =
    shmallocator.array::<f32>(0.0, 8);
  ctx.barrier_all();

  // Write into the array on the next
  // PE over.
  let mut remote =
    ctx.pe((my_pe + 1) % npes)
       .write(&mut shared, 0..8);
  for i in &mut remote[0..8] {
    *i = my_pe as _;
  }
  // Call finish on the MutableArrayView,
  // sending its data to the other PE.
  remote.finish();

  ctx.barrier_all();
  // Expected to be my_pe - 1 mod npes
  println!("pe {my_pe} sees {shared:?}");
  Ok(())
}
