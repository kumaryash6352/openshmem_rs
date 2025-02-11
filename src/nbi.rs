use std::{cell::UnsafeCell, marker::PhantomData, mem::{self, transmute, MaybeUninit}, ptr};

use crate::impl_nbiop_tuple;

/// The result of a non-blocking routine that
/// may not yet have been completed.
///
/// Use `ShmemCtx::quiet` to get the result.
#[must_use = "will panic if dropped without being passed to `ShmemCtx::quiet`"]
pub struct PendingNbiOp<'shm, T> {
    inner: Box<UnsafeCell<MaybeUninit<T>>>,
    _ctx: PhantomData<&'shm ()>
}

/// TODO: combine with PendingNbiOp
///       issues: maybeuninit<[]
#[must_use = "will panic if dropped without being passed to `ShmemCtx::quiet`"]
pub struct PendingNbiSliceOp<'shm, T> {
    inner: Box<UnsafeCell<[MaybeUninit<T>]>>,
    _ctx: PhantomData<&'shm ()>
}

// extern "C" {
//     fn MUST_USE_QUIET_ON_NBI();
// }

impl<'shm, T> PendingNbiOp<'shm, T> {
    /// # Safety
    /// self.inner MUST have been initialized
    unsafe fn into_inner(self) -> T {
        let inner;
        unsafe {
            inner = ptr::read_volatile(self.inner.get());
            mem::forget(self); // SAFETY: we WANT to bypass the constructor here
            inner.assume_init()
        }
    }
}

impl<'shm, T> PendingNbiSliceOp<'shm, T> {
    /// SAFETY: self.inner MUST have been initialized
    unsafe fn into_inner(self) -> Box<[T]> {
        let inner;
        unsafe {
            inner = ptr::read_volatile(&self.inner as *const _);
            mem::forget(self); // SAFETY: we WANT to bypass the constructor here

            // UnsafeCell is repr(transparent).
            // MaybeUninit is repr(transparent).
            // Therefore, Box<UnsafeCell<[MaybeUninit<T>]>> == Box<[T]>.
            // Maybe.
            transmute(inner)
        }
    }
}

impl<'shm, T> Drop for PendingNbiOp<'shm, T> {
    fn drop(&mut self) {
        // unsafe { MUST_USE_QUIET_ON_NBI(); }
        panic!("PendingNbiOp MUST be passed to ShmemCtx::quiet!
                You MUST NOT let this type be dropped!");
    }
}

impl<'shm, T> Drop for PendingNbiSliceOp<'shm, T> {
    fn drop(&mut self) {
        // unsafe { MUST_USE_QUIET_ON_NBI(); }
        panic!("PendingNbiSliceOp MUST be passed to ShmemCtx::quiet!
                You MUST NOT let this type be dropped!");
    }
}

pub(crate) unsafe fn nbi_op<'shm, T>(cell: Box<UnsafeCell<MaybeUninit<T>>>) -> PendingNbiOp<'shm, T> {
    PendingNbiOp { inner: cell, _ctx: PhantomData::default() }
}
pub(crate) unsafe fn nbi_slice_op<'shm, T>(cell: Box<UnsafeCell<[MaybeUninit<T>]>>) -> PendingNbiSliceOp<'shm, T> {
    PendingNbiSliceOp { inner: cell, _ctx: PhantomData::default() }
}

/// Common trait for PendingNbiOp and tuples
/// of PendingNbiOp.
///
/// Along with `PendingNbiOp`, this is also
/// implemented for tuples and vecs of `NbiOp`,
/// so you can finalize multiple operations in
/// one quiet.
pub trait NbiOp {
    /// What value does this NbiOp produce after a shmem_quiet?
    type Output;

    /// Unwrap the result of the NBI operation.
    ///
    /// # Safety
    /// Must be called after a `shmem_quiet`.
    unsafe fn after_quiet(self) -> Self::Output;
}

impl<T> NbiOp for PendingNbiOp<'_, T> {
    type Output = T;

    unsafe fn after_quiet(self) -> Self::Output {
        self.into_inner()
    }
}

impl<T> NbiOp for PendingNbiSliceOp<'_, T> {
    type Output = Box<[T]>;

    unsafe fn after_quiet(self) -> Self::Output {
        self.into_inner()
    }
}

impl<T> NbiOp for Vec<PendingNbiSliceOp<'_, T>> {
    type Output = Vec<T>;

    unsafe fn after_quiet(self) -> Self::Output {
        self.into_iter()
            // SAFETY: by requirements of after_quiet, shmem_quiet has been
            //         called and therefore the nbi routine has initialized
            //         this memory
            .map(|op| unsafe { op.into_inner() })
            .flatten()
            .collect()
    }
}

impl<T> NbiOp for Vec<PendingNbiOp<'_, T>> {
    type Output = Vec<T>;

    unsafe fn after_quiet(self) -> Self::Output {
        self.into_iter()
            // SAFETY: by requirements of after_quiet, shmem_quiet has been
            //         called and therefore the nbi routine has initialized
            //         this memory
            .map(|op| unsafe { op.into_inner() })
            .collect()
    }
}

// TODO: needed?
impl NbiOp for () {
    type Output = ();

    unsafe fn after_quiet(self) -> Self::Output {
        ()
    }
}

impl_nbiop_tuple!(A, B);
impl_nbiop_tuple!(A, B, C);
impl_nbiop_tuple!(A, B, C, D);
impl_nbiop_tuple!(A, B, C, D, E);
impl_nbiop_tuple!(A, B, C, D, E, F);
impl_nbiop_tuple!(A, B, C, D, E, F, G);
impl_nbiop_tuple!(A, B, C, D, E, F, G, H);
