use std::{cell::UnsafeCell, marker::PhantomData};

use bytemuck::{AnyBitPattern, Pod};

// TODO: `FakeAtomic[32/64]`: uses associated int32/64 routines
//                               to atomically edit a datatype.
use crate::{impl_atomic_bit, impl_atomic_fetch, impl_atomic_int, shmalloc::Shbox, ShmemCtx, PE};

/// An atomic version of a normal integer, float, or boolean.
///
/// This version can only be accessed by an instantaneous read or write:
/// see `Atomic::read()` or the assortment of `Atomic*` traits.
///
// # Safety
// The contained UnsafeCell must not be used for accessing the wrapped
// value EXCEPT in the case of a collective downgrade. OpenSHMEM
// atomic_* routines must be used instead.
pub struct Atomic<T: AtomicFetch>(UnsafeCell<T>);

/// Marker struct for a `ForceAtomicFetch` that's 32 bit.
#[derive(AnyBitPattern, Copy, Clone)]
pub struct Size32;
/// Marker struct for a `ForceAtomicFetch` that's 64 bit.
#[derive(AnyBitPattern, Copy, Clone)]
pub struct Size64;
/// Marker trait for a `ForceAtomicFetch` size.
pub trait Size {
    /// The type that has shmem routines for that size;
    type TreatAsA;
}
impl Size for Size32 {
    type TreatAsA = u32;
}
impl Size for Size64 {
    type TreatAsA = u64;
}

/// Wraps a 32 bit type, forcing atomic fetch, set, and swap operations
/// to be implemented.
///
/// Size of type is checked at compile time.
pub fn force_atomic32<T: Sized + Pod>(t: T) -> ForceAtomicFetch<T, Size32> {
    ForceAtomicFetch::<T, Size32>::new(t)
}

/// Wraps a 64 bit type, forcing atomic fetch, set, and swap operations
/// to be implemented.
///
/// Size of type is checked at compile time.
pub fn force_atomic64<T: Sized + Pod>(t: T) -> ForceAtomicFetch<T, Size64> {
    ForceAtomicFetch::<T, Size64>::new(t)
}

/// Forces a value to be compatible with atomic routines.
/// All constructions of this type are unsafe. The generic
/// must have a size of 32 or 64. This is enforced at compile time.
#[derive(AnyBitPattern, Copy, Clone)]
#[repr(transparent)]
pub struct ForceAtomicFetch<T: Sized + Pod, S: Size>(T, PhantomData<S>);

impl<T: Sized + Pod> ForceAtomicFetch<T, Size32> {
    fn new(t: T) -> Self {
        struct ForceSize<T, const S: usize>(T);
        impl<T, const Si: usize> ForceSize<T, Si> {
            const SIZE_MATCHES: () = assert!(size_of::<T>() == Si);
        }
        let _  = ForceSize::<T, 4>::SIZE_MATCHES;
        Self(t, Default::default())
    }
}
impl<T: Sized + Pod> ForceAtomicFetch<T, Size64> {
    fn new(t: T) -> Self {
        struct ForceSize<T, const S: usize>(T);
        impl<T, const Si: usize> ForceSize<T, Si> {
            const SIZE_MATCHES: () = assert!(size_of::<T>() == Si);
        }
        let _  = ForceSize::<T, 8>::SIZE_MATCHES;
        Self(t, Default::default())
    }
}


impl<T: Sized + Pod> AtomicFetch for ForceAtomicFetch<T, Size32>
{
    fn atomic_fetch(shbox: &Shbox<'_, Atomic<Self>>, from: PE, ctx: &ShmemCtx) -> Self {
        unsafe {
            bytemuck::cast( u32::atomic_fetch(std::mem::transmute(shbox), from, ctx) )
        }
    }

    fn atomic_set(shbox: &Shbox<'_, Atomic<Self>>, new: Self, to: PE, ctx: &ShmemCtx) {
        unsafe {
            bytemuck::cast( u32::atomic_set(std::mem::transmute(shbox), bytemuck::cast(new.0), to, ctx) )
        }
    }

    fn atomic_swap(shbox: &Shbox<'_, Atomic<Self>>, with: Self, to: PE, ctx: &ShmemCtx) -> Self {
        unsafe {
            bytemuck::cast( u32::atomic_swap(std::mem::transmute(shbox), bytemuck::cast(with.0), to, ctx) )
        }
    }
}
impl<T: Sized + Pod> AtomicFetch for ForceAtomicFetch<T, Size64>
{
    fn atomic_fetch(shbox: &Shbox<'_, Atomic<Self>>, from: PE, ctx: &ShmemCtx) -> Self {
        unsafe {
            bytemuck::cast( u64::atomic_fetch(std::mem::transmute(shbox), from, ctx) )
        }
    }

    fn atomic_set(shbox: &Shbox<'_, Atomic<Self>>, new: Self, to: PE, ctx: &ShmemCtx) {
        unsafe {
            bytemuck::cast( u64::atomic_set(std::mem::transmute(shbox), bytemuck::cast(new.0), to, ctx) )
        }
    }

    fn atomic_swap(shbox: &Shbox<'_, Atomic<Self>>, with: Self, to: PE, ctx: &ShmemCtx) -> Self {
        unsafe {
            bytemuck::cast( u64::atomic_swap(std::mem::transmute(shbox), bytemuck::cast(with.0), to, ctx) )
        }
    }
}

impl<T: AtomicFetch> Atomic<T> {
    /// Constructs a new Atomic from the value given.
    pub fn new(x: T) -> Self {
        Self(UnsafeCell::from(x))
    }

    /// Constructs a new Atomic using the default value of the type.
    pub fn default() -> Self
    where T: Default {
        Self(Default::default())
    }

    /// Aliases `UnsafeCell::get`
    fn get_cell_ptr(&self) -> *mut T {
        UnsafeCell::get(&self.0)
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
    note = "OpenSHMEM provides atomic math for 32 and 64 bit types"
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
impl_atomic_int!(usize, size);

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

#[cfg(target_pointer_width = "64")]
impl_atomic_bit!(usize, uint64);
#[cfg(target_pointer_width = "32")]
impl_atomic_bit!(usize, uint32);

impl<'ctx, T: AtomicFetch> Shbox<'ctx, Atomic<T>> {
    /// Fetch the value this atomic represents from another PE, or potentially this one.
    pub fn atomic_fetch_local(&self, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_fetch(self, ctx.my_pe(), ctx)
    }

    /// Fetch the value this atomic represents from another PE, or potentially this one.
    pub fn atomic_fetch(&self, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_fetch(self, pe, ctx)
    }

    /// Set the value this atomic represents on another PE, or potentially this one.
    pub fn atomic_set(&self, new_value: T, pe: PE, ctx: &'ctx ShmemCtx) {
        T::atomic_set(self, new_value, pe, ctx);
    }

    /// Swap the value this atomic represents on another PE, or potentially this one, and return their value
    pub fn atomic_swap(&self, new_value: T, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_swap(self, new_value, pe, ctx)
    }
}

impl<'ctx, T: AtomicInt> Shbox<'ctx, Atomic<T>> {
    /// Fetch the value this atomic represents from another PE, or potentially this one.
    pub fn atomic_inc(&self, pe: PE, ctx: &'ctx ShmemCtx) {
        T::atomic_inc(self, pe, ctx)
    }

    /// Fetch the value this atomic represents from another PE, or potentially this one, then increment the remote value.
    pub fn atomic_fetch_inc(&self, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_fetch_inc(self, pe, ctx)
    }

    /// Fetch the value this atomic represents from another PE, or potentially this one.
    pub fn atomic_add(&self, plus: T, pe: PE, ctx: &'ctx ShmemCtx) {
        T::atomic_add(self, plus, pe, ctx);
    }

    /// Fetch the value this atomic represents from another PE, or potentially this one.
    pub fn atomic_fetch_add(&self, plus: T, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_fetch_add(self, plus, pe, ctx)
    }

    /// Compare the remote value to `if_equals`. If the values are equal, set the remote value to `then_set_to`.
    /// Return the value pre-operation.
    pub fn atomic_compare_swap(&self, if_equals: T, then_set_to: T, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_compare_swap(self, if_equals, then_set_to, pe, ctx)
    }
}

impl<'ctx, T: AtomicBitwise> Shbox<'ctx, Atomic<T>> {
    /// And the value of this atomic on the given PE.
    pub fn atomic_and(&self, with: T, pe: PE, ctx: &'ctx ShmemCtx) {
        T::atomic_and(self, with, pe, ctx)
    }
    /// And the value of this atomic on the given PE, and fetch the value pre-operation.
    pub fn atomic_fetch_and(&self, with: T, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_fetch_and(self, with, pe, ctx)
    }

    /// Or the value of this atomic on the given PE.
    pub fn atomic_or(&self, with: T, pe: PE, ctx: &'ctx ShmemCtx) {
        T::atomic_or(self, with, pe, ctx)
    }
    /// Or the value of this atomic on the given PE, and fetch the value pre-operation.
    pub fn atomic_fetch_or(&self, with: T, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_fetch_or(self, with, pe, ctx)
    }

    /// Xor the value of this atomic on the given PE.
    pub fn atomic_xor(&self, with: T, pe: PE, ctx: &'ctx ShmemCtx) {
        T::atomic_xor(self, with, pe, ctx)
    }
    /// Xor the value of this atomic on the given PE, and fetch the value pre-operation.
    pub fn atomic_fetch_xor(&self, with: T, pe: PE, ctx: &'ctx ShmemCtx) -> T {
        T::atomic_fetch_xor(self, with, pe, ctx)
    }
}
