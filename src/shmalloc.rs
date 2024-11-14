use std::{
    alloc::{AllocError, Allocator, Layout},
    ffi::{c_long, c_void},
    fmt::Debug,
    mem::{self, MaybeUninit},
    ops::{Deref, DerefMut, RangeBounds},
    ptr::NonNull,
};

use openshmem_sys::shmem::{
    shmem_align, shmem_calloc, shmem_free, shmem_putmem, shmem_realloc,
};

use crate::{ShmemCtx, PE};

/// The Shmallocator handles [de]allocations on the Symmetric Heap.
/// Note that, as the `'ctx` lifetime indicates, the ShmemCtx must outlive the Shmallocator.
pub struct Shmallocator<'ctx> {
    // We hold on to the ctx so we can verify
    // that we have not shmem_finalize'd.
    //
    // Technically, we could've just PhantomDataL<&'ctx ()>,
    // but this is clearer.
    #[expect(unused, reason = "ctx held on to for future use")]
    ctx: &'ctx ShmemCtx,
}

impl<'ctx> From<&'ctx ShmemCtx> for Shmallocator<'ctx> {
    fn from(ctx: &'ctx ShmemCtx) -> Self {
        Self { ctx }
    }
}

unsafe impl<'ctx> Allocator for Shmallocator<'ctx> {
    fn allocate(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        let ptr = unsafe { shmem_align(layout.align(), layout.size()) };
        Ok(NonNull::slice_from_raw_parts(
            NonNull::new(ptr as *mut u8).ok_or(AllocError)?,
            layout.size(),
        ))
    }

    unsafe fn deallocate(&self, ptr: std::ptr::NonNull<u8>, _layout: std::alloc::Layout) {
        unsafe { shmem_free(ptr.as_ptr() as *mut c_void) }
    }

    unsafe fn grow(
        &self,
        ptr: NonNull<u8>,
        _old_layout: Layout, // how openshmem doesn't need the old layout, i have no clue.
        new_layout: Layout,
    ) -> Result<NonNull<[u8]>, AllocError> {
        let ptr = shmem_realloc(ptr.as_ptr() as *mut c_void, new_layout.size());
        Ok(NonNull::slice_from_raw_parts(
            NonNull::new(ptr as *mut u8).ok_or(AllocError)?,
            new_layout.size(),
        ))
    }

    unsafe fn shrink(
        &self,
        ptr: NonNull<u8>,
        _old_layout: Layout, // how openshmem doesn't need the old layout, i have no clue.
        new_layout: Layout,
    ) -> Result<NonNull<[u8]>, AllocError> {
        self.grow(ptr, _old_layout, new_layout)
    }

    fn allocate_zeroed(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        // SAFETY: If shmem_calloc can't allocate, it returns null.
        //         NonNull::new checks for null.
        //
        // SAFETY: We allocate enough data as per the documentation
        //         of shmem_calloc.
        let ptr = unsafe { shmem_calloc(1, layout.size()) };
        NonNull::new(ptr as *mut u8)
            .map(|nn| NonNull::slice_from_raw_parts(nn, layout.size()))
            .ok_or(AllocError)
    }
}

impl<'ctx> Shmallocator<'ctx> {
    // Constructs a shared Vec for the given type.
    //
    // Note that this is a collective operation. All
    // PEs must participate.
    // TODO: Vecs realloc. How does SHMEM handle this?
    // pub fn vec<T>(&self) -> Vec<T, &Shmallocator<'ctx>> {
    //     Vec::new_in(self)
    // }

    /// Constructs a shared mutable slice with at least `len` `T::default()`'s.
    ///
    /// Note that this type is technically unsound. I don't know how to fix that yet.
    pub fn array_default<T: Default>(&'ctx self, len: usize) -> Shbox<'ctx, [T]> {
        let mut vec = Box::new_zeroed_slice_in(len, self);
        vec.fill_with(|| MaybeUninit::new(T::default()));
        // SAFETY: The `fill_with` has initializaed all elements of vec.
        Shbox {
            internal: unsafe { mem::transmute(vec) },
            #[cfg(feature = "lockshbox")]
            lock: Box::new_in(0, self)
        }
    }

    /// Constructs a shared mutable slice with at least `len` `f(usize)`'s.
    /// The parameter passed to `f` is the index being filled.
    ///
    /// Note that this type is technically unsound. I don't know how to fix that yet.
    pub fn array_gen<T>(&'ctx self, mut f: impl FnMut(usize) -> T, len: usize) -> Shbox<'ctx, [T]> {
        let mut vec = Box::new_zeroed_slice_in(len, self);
        for (idx, e) in vec.iter_mut().enumerate() {
            *e = MaybeUninit::new(f(idx));
        }
        // SAFETY: The `fill_with` has initializaed all elements of vec.
        Shbox {
            internal: unsafe { mem::transmute(vec) },
            #[cfg(feature = "lockshbox")]
            lock: Box::new_in(0, self)
        }
    }

    /// Constructs a shared mutable slice with at least `len` `t's.
    ///
    /// Note that this type is technically unsound. I don't know how to fix that yet.
    pub fn array<T: Clone>(&'ctx self, t: T, len: usize) -> Shbox<'ctx, [T]> {
        let mut vec = Box::new_zeroed_slice_in(len, self);
        vec.fill_with(|| MaybeUninit::new(t.clone()));
        // SAFETY: The `fill_with` has initializaed all elements of vec.
        Shbox {
            internal: unsafe { mem::transmute(vec) },
            #[cfg(feature = "lockshbox")]
            lock: Box::new_in(0, self)
        }
    }

    /// Constructs a shared Box for the given type.
    ///
    /// Note that this is a collective operation. All
    /// PEs must participate.
    pub fn shbox<T>(&'ctx self, t: T) -> Shbox<'ctx, T> {
        Shbox {
            internal: Box::new_in(t, self),
            #[cfg(feature = "lockshbox")]
            lock: Box::new_in(0, self)
        }
    }
}

/// A Shbox<T> is a T on the symmetric heap.
///
/// Constructed using methods on a `Shmallocator`.
pub struct Shbox<'ctx, T: ?Sized> {
    internal: Box<T, &'ctx Shmallocator<'ctx>>,
    #[cfg(feature = "lockshbox")]
    lock: Box<c_long, &'ctx Shmallocator<'ctx>>
}

impl<'ctx, T: ?Sized> Shbox<'ctx, T> {
    /// Retrieve a reference to the underlying type.
    ///
    /// This is equivalent to `Deref::deref`'ing a `Shbox`.
    #[cfg(not(feature = "lockshbox"))]
    pub fn raw(&self) -> &T {
        self.internal.as_ref()
    }

    /// Retrieve a raw pointer to the underlying type.
    ///
    /// This pointer will point to the symmetric heap.
    pub fn raw_ptr(&self) -> *const T {
        self.internal.as_ref() as _
    }

    /// Retrieve a raw mutable pointer to the underlying type.
    ///
    /// This pointer will point to the symmetric heap.
    pub fn raw_ptr_mut(&mut self) -> *mut T {
        self.internal.as_mut() as _
    }

    #[cfg(feature = "lockshbox")]
    pub fn lock<'a>(&'a mut self) -> ShboxLock<'a, 'ctx, T> {
        use openshmem_sys::shmem::shmem_set_lock;

        unsafe { shmem_set_lock(self.lock.as_mut() as *mut c_long) }
        ShboxLock {
            shbox: self
        }
    }
}

/// A lock on a Shbox. Equivalent to locking a Mutex for the Shbox.
/// It is guaranteed no other PEs may access the Shbox while this lock exists.
pub struct ShboxLock<'shbox, 'ctx: 'shbox, T: ?Sized> {
    shbox: &'shbox mut Shbox<'ctx, T>,
}

impl<'shbox, 'ctx, T: ?Sized> Deref for ShboxLock<'shbox, 'ctx, T> {
    type Target = T;

    fn deref(&self) -> &T {
        self.shbox.internal.deref()
    }
}
impl<'shbox, 'ctx, T: ?Sized> DerefMut for ShboxLock<'shbox, 'ctx, T> {
    fn deref_mut(&mut self) -> &mut T {
        self.shbox.internal.deref_mut()
    }
}

#[cfg(not(feature = "lockshbox"))]
impl<'ctx, T: ?Sized> Deref for Shbox<'ctx, T> {
    type Target = T;

    fn deref(&self) -> &T {
        self.internal.deref()
    }
}

#[cfg(not(feature = "lockshbox"))]
impl<'ctx, T: ?Sized> DerefMut for Shbox<'ctx, T> {
    fn deref_mut(&mut self) -> &mut T {
        self.internal.deref_mut()
    }
}

#[cfg(not(feature = "lockshbox"))]
impl<'ctx, T0: ?Sized + Debug> Debug for Shbox<'ctx, T0> {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        <Box<T0, &'ctx Shmallocator<'ctx>> as Debug>::fmt(&self.internal, f)
    }
}

/// A view into an array on a remote PE.
///
/// No matter whether it has been written to, the internal
/// buffer will be copied back to the remote host. If you
/// only want to read data from the remote host, see `Shbox::read_from`.
pub struct MutableArrayView<'ctx, 'shbox, T, R>
where
    R: RangeBounds<usize> + Clone,
    'ctx: 'shbox,
{
    pub(crate) _ctx: &'ctx ShmemCtx,
    pub(crate) into: &'shbox mut Shbox<'ctx, [T]>,
    pub(crate) range: R,
    pub(crate) on: PE,
    pub(crate) buf: Box<[T]>,
}

pub(crate) fn apply_range_bounds<R: RangeBounds<usize>, T>(bounds: R, t: &[T]) -> (usize, usize) {
    let end = match bounds.end_bound() {
        std::ops::Bound::Included(x) => *x,
        std::ops::Bound::Excluded(x) => *x - 1,
        std::ops::Bound::Unbounded => t.len(),
    };
    let start = match bounds.start_bound() {
        std::ops::Bound::Included(x) => *x,
        std::ops::Bound::Excluded(x) => *x + 1,
        std::ops::Bound::Unbounded => 0,
    };
    (start, end)
}

impl<'ctx, 'shbox, T, R> Drop for MutableArrayView<'ctx, 'shbox, T, R>
where
    R: RangeBounds<usize> + Clone,
    'ctx: 'shbox,
{
    fn drop(&mut self) {
        let (start, end) = apply_range_bounds(self.range.clone(), &self.buf);
        unsafe {
            shmem_putmem(
                (self.into.internal.as_ref() as *const [T] as *const T).offset(start as _) as *mut c_void,
                self.buf.as_ptr() as *const c_void,
                size_of::<T>() * (end - start + 1),
                self.on.0 as _,
            );
        }
    }
}

impl<'ctx, 'shbox, T, R> MutableArrayView<'ctx, 'shbox, T, R>
where
    R: RangeBounds<usize> + Clone,
    'ctx: 'shbox,
{
    /// Immediately push data to the remote PE.
    ///
    /// This is equivalent to dropping the view.
    ///
    /// In fact, the body is `drop(self)`.
    pub fn finish(self) {
        drop(self)
    }
}

impl<'ctx, 'shbox, T, R> Deref for MutableArrayView<'ctx, 'shbox, T, R>
where
    R: RangeBounds<usize> + Clone,
{
    type Target = [T];

    fn deref(&self) -> &Self::Target {
        self.buf.as_ref()
    }
}

impl<'ctx, 'shbox, T, R> DerefMut for MutableArrayView<'ctx, 'shbox, T, R>
where
    R: RangeBounds<usize> + Clone,
{
    fn deref_mut(&mut self) -> &mut Self::Target {
        self.buf.as_mut()
    }
}
