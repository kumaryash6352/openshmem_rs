use crate::shmalloc::Shbox;
use crate::impl_waitable;
use openshmem_sys::shmem::{
    SHMEM_CMP_EQ, SHMEM_CMP_GE, SHMEM_CMP_GT, SHMEM_CMP_LE, SHMEM_CMP_LT, SHMEM_CMP_NE,
};

/// Comparison operators for the wait_until family of methods.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u32)]
pub enum ShmemCompareOp {
    /// x == y (SHMEM_CMP_EQ)
    Equal = SHMEM_CMP_EQ,
    /// x != y (SHMEM_CMP_NE)
    NotEqual = SHMEM_CMP_NE,
    /// x > y (SHMEM_CMP_GT)
    Greater = SHMEM_CMP_GT,
    /// x >= y (SHMEM_CMP_GE)
    GreaterEqual = SHMEM_CMP_GE,
    /// x < y (SHMEM_CMP_LT)
    Lesser = SHMEM_CMP_LT,
    /// x <= y (SHMEM_CMP_LE)
    LesserEqual = SHMEM_CMP_LE,
}

/// Types that have shmem_wait_until routines.
///
/// See `Shbox` for safe wrappers of these methods.
#[diagnostic::on_unimplemented(
    message = "no OpenSHMEM routine for waits into {Self}",
    label = "this {Self} here",
    note = "OpenSHMEM provides wait routines for [i/u][32, 64, size]"
)]
pub trait Waitable: Sized {
    /// Blocks, waiting until the value matches the given value and op.
    unsafe fn wait_until(shbox: &mut Shbox<'_, Self>, op: ShmemCompareOp, x: Self);
    /// Blocks, waiting until all values match the given value and op.
    unsafe fn wait_until_all(shbox: &mut Shbox<'_, [Self]>, op: ShmemCompareOp, x: Self);
    /// Blocks, waiting until some values match the given value and op.
    unsafe fn wait_until_some(
        shbox: &mut Shbox<'_, [Self]>,
        op: ShmemCompareOp,
        x: Self,
    ) -> Vec<usize>;
    /// Blocks, waiting until some values match the given value and op.
    /// Returns a vector of indices of the values that matched.
    unsafe fn wait_until_any(shbox: &mut Shbox<'_, [Self]>, op: ShmemCompareOp, x: Self) -> usize;
}

impl_waitable!(u32, uint32);
impl_waitable!(i32, int32);
impl_waitable!(u64, uint64);
impl_waitable!(i64, int64);
impl_waitable!(usize, size);
