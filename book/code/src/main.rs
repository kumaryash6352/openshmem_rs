mod benchmark;
mod sequential;
mod thread_parallel;

use crate::sequential::Sequential;
use crate::thread_parallel::ThreadParallel;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    benchmark::bench::<ThreadParallel>()?;
    Ok(())
}
