use std::error::Error;

use openshmem_macros::Shend;
use openshmem_rs::{traits::Shend, ShmemCtx};

// Before a type may be used on the Symmetric Heap (SH),
// it must be Shend.
//
// Most of the basic types (unsigned/signed ints, floats)
// are already Shend and can be used as-is.
//
// User types may derive Shend if all their components are Shend,
// or unsafely implement Shend if they know their type should be safe.
#[derive(Shend, Copy, Clone)]
pub struct Vec3 {
    pub x: f32,
    pub y: f32,
    pub z: f32
}

const ZERO: Vec3 = Vec3 {
    x: 0.0,
    y: 0.0,
    z: 0.0
};

fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let shm = ctx.shmallocator();

    let basic_types = (shm.shbox(0usize), shm.shbox(0isize), shm.shbox('a'), shm.shbox(2.0f32));

    // Shend is a requirement. Non-Shend types cannot be placed on the SH.
    // let will_error = shm.shbox(File::open("/etc/hostname"));

    let user_type = shm.shbox(ZERO);
    let array_user_type = shm.array_gen(|_| ZERO, 256);


    Ok(())
}
