#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

// NOTE: As of 1.78, i128/u128 are both ABI-compatible
//       with C's __int128/__uint128_t. However, usage of
//       either across the FFI boundary still emits a warning
//       because, outside of x86, Rust still isn't putting
//       any guarantees on what happens. Remove this allow
//       ASAP.
#![allow(improper_ctypes)]

pub mod shmem;

#[cfg(feature = "shmemx")]
pub mod shmemx;
