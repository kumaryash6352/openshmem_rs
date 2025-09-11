use crate::impl_shend_tuple;
pub use openshmem_macros::Shend;

/// A safe (enough) type for PGAS operations.
///
/// Shend is analoguous to Send, but across PEs instead of threads.
/// A Shend type may be sent (put/get) across PEs.
///
/// Usually, you don't implement this trait yourself. Common types,
/// such as integers, floats, bools, and chars, already implement Shend.
/// If you have a type you want to read remotely, you can derive Shend through the proc-macro.
/// The macro requires ALL types your type is made of must also implement Shend.
pub unsafe trait Shend: Clone {}

unsafe impl Shend for u8 {}
unsafe impl Shend for u16 {}
unsafe impl Shend for u32 {}
unsafe impl Shend for u64 {}
unsafe impl Shend for usize {}
unsafe impl Shend for i8 {}
unsafe impl Shend for i16 {}
unsafe impl Shend for i32 {}
unsafe impl Shend for i64 {}
unsafe impl Shend for isize {}

unsafe impl Shend for f32 {}
unsafe impl Shend for f64 {}

unsafe impl Shend for char {}
unsafe impl Shend for bool {}

unsafe impl<const N: usize, T: Shend> Shend for [T; N] {}

#[cfg_attr(docsrs, doc(fake_variadic))]
impl_shend_tuple!(A, B);
impl_shend_tuple!(A, B, C);
impl_shend_tuple!(A, B, C, D);
impl_shend_tuple!(A, B, C, D, E);
impl_shend_tuple!(A, B, C, D, E, F);
