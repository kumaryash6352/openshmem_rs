// TODO: `FakeAtomic[32/64]`: uses associated int32/64 routines
//                               to atomically edit a datatype.
use crate::{impl_atomic_bit, impl_atomic_fetch, impl_atomic_int, shmalloc::Shbox, ShmemCtx, PE};

/// An atomic version of a normal integer, float, or boolean.
///
/// This version can only be accessed by an instantaneous read or write:
/// see `Atomic::read()` or the assortment of `Atomic*` traits.
pub struct Atomic<T: AtomicFetch>(T);

impl<T: AtomicFetch> Atomic<T> {
    /// Constructs a new Atomic from the value given.
    pub fn new(x: T) -> Self {
        Self(x)
    }

    /// Constructs a new Atomic using the default value of the type.
    pub fn default() -> Self
    where T: Default {
        Self(Default::default())
    }

    /// Atomically reads the local value.
    pub fn fetch_local(shbox: &Shbox<'_, Self>, ctx: &ShmemCtx) -> T {
        T::atomic_fetch(shbox, ctx.my_pe(), ctx)
    }

    /// Fetch the value of the atomic from the given PE.
    pub fn fetch(shbox: &Shbox<'_, Self>, from: PE, ctx: &ShmemCtx) -> T {
        T::atomic_fetch(shbox, from, ctx)
    }
}

/// Represents types that have a `shmem_atomic_[fetch/set]`.
///
/// See `Shbox` for safe wrappers of these methods.
#[diagnostic::on_unimplemented(
    message = "no OpenSHMEM routine for atomic fetch/set/swap for {Self}",
    label = "this {Self} here",
    note = "OpenSHMEM provides set/get/swap for 32 and 64 bit types"
)]
pub trait AtomicFetch: Sized {
    /// Apply `shmem_[typename]_fetch`.
    fn atomic_fetch(shbox: &Shbox<'_, Atomic<Self>>, from: PE, ctx: &ShmemCtx) -> Self;
    /// Apply `shmem_[typename]_set`.
    fn atomic_set(shbox: &Shbox<'_, Atomic<Self>>, new: Self, to: PE, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_swap`.
    fn atomic_swap(shbox: &Shbox<'_, Atomic<Self>>, with: Self, to: PE, ctx: &ShmemCtx) -> Self;
}

impl_atomic_fetch!(u32, uint32);
impl_atomic_fetch!(i32, int32);
impl_atomic_fetch!(u64, uint64);
impl_atomic_fetch!(i64, int64);
impl_atomic_fetch!(f32, float);
impl_atomic_fetch!(f64, double);
impl_atomic_fetch!(usize, size);

/// Represents types that have a `shmem_atomic_[compare_swap/inc/add]`.
///
/// See `Shbox` for safe wrappers of these methods.
#[diagnostic::on_unimplemented(
    message = "no OpenSHMEM routine for atomic math on {Self}",
    label = "this {Self} here",
    note = "OpenSHMEM provides set/get for 32 and 64 bit types"
)]
pub trait AtomicInt: Sized + AtomicFetch {
    /// Apply `shmem_[typename]_compare_swap`.
    fn atomic_compare_swap(shbox: &Shbox<'_, Atomic<Self>>, if_equals: Self, then_set_to: Self, on: PE, ctx: &ShmemCtx) -> Self;
    /// Apply `shmem_[typename]_fetch_inc`.
    ///
    /// Returns the old value, then increments the value on the target PE.
    fn atomic_fetch_inc(shbox: &Shbox<'_, Atomic<Self>>, from: PE, ctx: &ShmemCtx) -> Self;
    /// Apply `shmem_[typename]_inc`.
    fn atomic_inc(shbox: &Shbox<'_, Atomic<Self>>, to: PE, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_fetch_add`.
    ///
    /// Returns the old value, then adds `plus` to the value on the target PE.
    fn atomic_fetch_add(shbox: &Shbox<'_, Atomic<Self>>, plus: Self, from: PE, ctx: &ShmemCtx) -> Self;
    /// Apply `shmem_[typename]_add`.
    fn atomic_add(shbox: &Shbox<'_, Atomic<Self>>, plus: Self, to: PE, ctx: &ShmemCtx);
}

impl_atomic_int!(u32, uint32);
impl_atomic_int!(i32, int32);
impl_atomic_int!(u64, uint64);
impl_atomic_int!(i64, int64);

/// Represents types that have a `shmem_atomic_and/or/xor`.
///
/// See `Shbox` for safe wrappers of these methods.
#[diagnostic::on_unimplemented(
    message = "no OpenSHMEM routine for atomic bitmath on {Self}",
    label = "this {Self} here",
    note = "OpenSHMEM provides set/get for 32 and 64 bit types"
)]
pub trait AtomicBitwise: Sized + AtomicFetch {
    /// Apply `shmem_[typename]_fetch_and`.
    ///
    /// Returns the old value, then sets the target PE's value to `with & *shbox`.
    fn atomic_fetch_and(shbox: &Shbox<'_, Atomic<Self>>, with: Self, from: PE, ctx: &ShmemCtx) -> Self;
    /// Apply `shmem_[typename]_and`.
    fn atomic_and(shbox: &Shbox<'_, Atomic<Self>>, with: Self, to: PE, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_fetch_or`.
    ///
    /// Returns the old value, then sets the target PE's value to `with | *shbox`.
    fn atomic_fetch_or(shbox: &Shbox<'_, Atomic<Self>>, with: Self, from: PE, ctx: &ShmemCtx) -> Self;
    /// Apply `shmem_[typename]_or`.
    fn atomic_or(shbox: &Shbox<'_, Atomic<Self>>, with: Self, to: PE, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_fetch_xor`.
    ///
    /// Returns the old value, then sets the target PE's value to `with ^ *shbox`.
    fn atomic_fetch_xor(shbox: &Shbox<'_, Atomic<Self>>, with: Self, from: PE, ctx: &ShmemCtx) -> Self;
    /// Apply `shmem_[typename]_xor`.
    fn atomic_xor(shbox: &Shbox<'_, Atomic<Self>>, with: Self, to: PE, ctx: &ShmemCtx);
}

impl_atomic_bit!(u32, uint32);
impl_atomic_bit!(i32, int32);
impl_atomic_bit!(u64, uint64);
impl_atomic_bit!(i64, int64);

impl<'ctx, T: AtomicFetch> Shbox<'ctx, Atomic<T>> {}
