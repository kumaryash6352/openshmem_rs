use std::ffi::c_long;

use openshmem_sys::shmem::{shmem_clear_lock, shmem_set_lock};

use crate::shmalloc::{Shbox, Shmallocator};

/// An OpenSHMEM lock.
///
/// Acquire the lock with `Shmlock::lock`, which returns a `ShmlockLock`.
/// When the `ShmlockLock` is `drop`ed, the lock is released.
pub struct Shmlock<'ctx>(Shbox<'ctx, c_long>);

/// A struct representing the lock on a `Shmlock`.
/// So long as this struct lives, the `Shmlock` is locked.
pub struct ShmlockLock<'ctx, 'shmlock>(&'shmlock Shmlock<'ctx>);
impl<'ctx, 'shmlock> Drop for ShmlockLock<'ctx, 'shmlock> {
    fn drop(&mut self) {
        unsafe { shmem_clear_lock(self.0 .0.raw_ptr() as *mut c_long) }
    }
}

impl<'ctx> Shmlock<'ctx> {
    /// Construct a `Shmlock` using the given `Shmallocator`.
    ///
    /// It's recommended to instead use the `Shmallocator::lock` method.
    ///
    /// This is a collective operation.
    pub fn new(shmalloc: &'ctx Shmallocator) -> Self {
        Shmlock(shmalloc.shbox(0))
    }

    /// Acquire a lock for this `Shmlock`.
    ///
    /// When dropped, the lock is cleared.
    #[doc(alias = "acquire")]
    pub fn lock<'shmlock>(&'shmlock self) -> ShmlockLock<'ctx, 'shmlock> {
        unsafe { shmem_set_lock(self.0.raw_ptr() as *mut c_long) };
        ShmlockLock(self)
    }
}
