use std::{
    alloc::{AllocError, Allocator, Layout},
    cell::UnsafeCell,
    ffi::c_void,
    fmt::Debug,
    mem::{self, transmute, ManuallyDrop, MaybeUninit},
    ops::{Bound, Deref, DerefMut, Index, RangeBounds},
    ptr::NonNull,
};

use openshmem_sys::shmem::{
    shmem_align, shmem_alltoallmem, shmem_calloc, shmem_free, shmem_getmem, shmem_getmem_nbi,
    shmem_putmem, shmem_putmem_nbi, shmem_realloc, shmem_team_t,
};

use crate::{
    atomics::{Atomic, AtomicFetch},
    nbi::{nbi_noout_op, PendingNbiOp, PendingNbiSliceOp, PendingNbiUnitOp},
    nbi_op, nbi_slice_op,
    shmutex::Shmlock,
    traits::Shend,
    ShmemCtx, PE,
};

/// The Shmallocator handles [de]allocations on the Symmetric Heap.
/// Note that, as the `'ctx` lifetime indicates, the ShmemCtx must outlive the Shmallocator.
pub struct Shmallocator<'ctx> {
    // We hold on to the ctx so we can verify
    // that we have not shmem_finalize'd.
    //
    // Technically, we could've just PhantomData<&'ctx ()>,
    // but this is clearer.
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
    pub fn array_default<T: Shend + Default>(&'ctx self, len: usize) -> Shbox<'ctx, [T]> {
        let mut cap = self.shbox(len);
        cap.reduce_max(self.ctx);
        let mut vec = Box::new_zeroed_slice_in(*cap, self);
        vec.fill_with(|| MaybeUninit::new(T::default()));
        // SAFETY: The `fill_with` has initializaed all elements of vec.
        Shbox {
            internal: unsafe { mem::transmute(vec) },
        }
    }

    /// Constructs a shared mutable slice with at least `len` `f(usize)`'s.
    /// The parameter passed to `f` is the index being filled.
    ///
    /// Each PE will generate it's own elements. If you want to instead generate `len` elements
    /// in total, consider combining this with `Shbox::collect`
    pub fn array_gen<T: Shend>(
        &'ctx self,
        mut f: impl FnMut(usize) -> T,
        len: usize,
    ) -> Shbox<'ctx, [T]> {
        let mut cap = self.shbox(len);
        cap.reduce_max(self.ctx);
        let mut vec = Box::new_zeroed_slice_in(*cap, self);
        for (idx, e) in vec.iter_mut().enumerate() {
            *e = MaybeUninit::new(f(idx));
        }
        // SAFETY: The `fill_with` has initializaed all elements of vec.
        Shbox {
            internal: unsafe { mem::transmute(vec) },
        }
    }

    /// Constructs a shared mutable slice with at least `len` `t's.
    ///
    /// Note that this type is technically unsound. I don't know how to fix that yet.
    pub fn array<T: Shend>(&'ctx self, t: T, len: usize) -> Shbox<'ctx, [T]> {
        let mut cap = self.shbox(len);
        cap.reduce_max(self.ctx);
        let mut vec = Box::new_zeroed_slice_in(*cap, self);
        vec.fill_with(|| MaybeUninit::new(t.clone()));
        // SAFETY: The `fill_with` has initializaed all elements of vec.
        Shbox {
            internal: unsafe { mem::transmute(vec) },
        }
    }

    /// Constructs a shared Box for the given type.
    ///
    /// Note that this is a collective operation. All
    /// PEs must participate.
    pub fn shbox<T: Shend>(&'ctx self, t: T) -> Shbox<'ctx, T> {
        Shbox {
            internal: Box::new_in(t, self),
        }
    }

    /// Constructs a Lock.
    ///
    /// This is a collective operation.
    #[doc(alias = "shmlock")]
    pub fn lock(&self) -> Shmlock<'_> {
        Shmlock::new(&self)
    }
}

/// A Shbox<T> is a T on the symmetric heap.
///
/// Constructed using methods on a `Shmallocator`.
pub struct Shbox<'ctx, T: ?Sized> {
    internal: Box<T, &'ctx Shmallocator<'ctx>>,
}

impl<'ctx, T: ?Sized> Shbox<'ctx, T> {
    pub fn shptr<'s>(&'s self) -> Shptr<&'s T> {
        Shptr { internal: &self.internal }
    }

    /// Retrieve a reference to the underlying type.
    ///
    /// This is equivalent to `Deref::deref`'ing a `Shbox`.
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

    // pub fn drop_take(self, _ctx: &ShmemCtx) -> Box<T> {
    //     let size = size_of_val(self.internal.as_ref());
    //     self.
    // }
}

impl<'ctx, T: ?Sized + Shend> Shbox<'ctx, T> {
    pub fn put(&mut self, data: &T, pe: PE, _ctx: &ShmemCtx) {
        unsafe {
            shmem_putmem(
                self.raw_ptr_mut() as *mut c_void,
                data as *const T as *const c_void,
                size_of::<T>(),
                pe.0 as _,
            );
        }
    }

    /// Read the remote element of the Shbox.
    pub fn get(&self, pe: PE, _ctx: &ShmemCtx) -> T {
        let mut buffer = MaybeUninit::uninit();
        unsafe {
            shmem_getmem(
                buffer.as_mut_ptr() as *mut c_void,
                self.raw_ptr() as *const c_void,
                size_of::<T>(),
                pe.0 as _,
            );
        }
        unsafe { buffer.assume_init() }
    }

    pub fn put_nbi<'s>(&'s mut self, data: &T, pe: PE) -> PendingNbiOp<'s, ()> {
        let buffer = Box::new(UnsafeCell::new(MaybeUninit::new(())));
        unsafe {
            shmem_putmem_nbi(
                self.raw_ptr_mut() as *mut c_void,
                data as *const T as *const c_void,
                size_of::<T>(),
                pe.0 as _,
            );
        }
        unsafe { nbi_op(buffer) }
    }

    pub fn get_nbi<'s>(&'s self, pe: PE) -> PendingNbiOp<'s, T> {
        let buffer = Box::new(UnsafeCell::new(MaybeUninit::uninit()));
        unsafe {
            shmem_getmem_nbi(
                buffer.get() as *mut c_void,
                self.raw_ptr() as *const c_void,
                size_of::<T>(),
                pe.0 as _,
            );
        }
        unsafe { nbi_op(buffer) }
    }
}

impl<'ctx, T: Sized + Shend> Shbox<'ctx, [T]> {
    pub fn slice<'s, R>(&'s self, range: R) -> Shptr<&[T]>
    where
        R: RangeBounds<usize> + std::slice::SliceIndex<[T], Output = [T]>,
        for<'a> &'a [T]: Index<R>,
    {
        Shptr {
            internal: &self.internal[range],
        }
    }

    pub fn slice_mut<'s, R>(&'s mut self, range: R) -> Shptr<&'s mut [T]>
    where
        R: RangeBounds<usize> + std::slice::SliceIndex<[T], Output = [T]>,
        for<'a> &'a mut [T]: Index<R>,
    {
        Shptr {
            internal: &mut self.internal[range],
        }
    }

    /// Instantly replace the `offset..(offset + data.len())` elements of `shbox @ PE`
    /// with the elements from `data`.
    ///
    /// # Panics
    /// If `data.len() > shbox.len()`, panic.
    pub fn put_many(&mut self, offset: usize, data: &[T], pe: PE, _ctx: &ShmemCtx) {
        if data.len() + offset > self.len() {
            panic!("tried to write more data into a shbox than would fit!");
        }

        // SAFETY: shbox is on the symmetric heap by construction
        //         shbox has room for at laest data.len() elements,
        //         or we would've panicked
        unsafe {
            shmem_putmem(
                self.as_mut_ptr().offset(offset as _) as *mut c_void,
                data.as_ptr() as *const c_void,
                size_of::<T>() * data.len(),
                pe.0 as _,
            );
        }
    }

    pub fn put_single(&mut self, idx: usize, data: &T, pe: PE, _ctx: &ShmemCtx) {
        assert!(
            idx < self.len(),
            "tried to idx out of bounds: len {}, idx {idx}",
            self.len()
        );
        unsafe {
            shmem_putmem(
                self.as_mut_ptr().offset(idx as _) as *mut c_void,
                data as *const T as *const c_void,
                size_of::<T>(),
                pe.0 as _,
            );
        }
    }

    /// Reads a slice from the `Shbox` on another PE.
    pub fn get_many<R>(&self, pe: PE, range: R, _ctx: &ShmemCtx) -> Box<[T]>
    where
        R: RangeBounds<usize> + Clone,
    {
        let (start, end) = apply_range_bounds(range.clone(), self.as_ref());
        let buffer_size = end - start;
        let mut buffer: Box<[MaybeUninit<T>]> = Box::new_uninit_slice(buffer_size);
        // SAFETY: shbox is on the symmetric heap since, well, it's a shbox.
        //         we know buffer has enough capacity since we derived n_elems
        //         from the range asked
        unsafe {
            shmem_getmem(
                buffer.as_mut_ptr() as *mut c_void,
                (self.as_ref() as *const [T] as *const T).offset(start as _) as *mut c_void,
                buffer_size * size_of::<T>(),
                pe.0 as _,
            )
        }
        // SAFETY: T is Pod, and so any bit representation is a valid T.
        //         Therefore, even if we read data unset by shmem_getmem,
        //         we read valid T's.
        unsafe { mem::transmute(buffer) }
    }

    pub fn get_single(&self, pe: PE, idx: usize, _ctx: &ShmemCtx) -> T {
        assert!(
            idx < self.len(),
            "tried to idx out of bounds: len {}, idx {idx}",
            self.len()
        );
        let mut buffer = MaybeUninit::uninit();
        unsafe {
            shmem_getmem(
                buffer.as_mut_ptr() as *mut c_void,
                (self.as_ref() as *const [T] as *const T).offset(idx as _) as *mut c_void,
                size_of::<T>(),
                pe.0 as _,
            );
        }
        unsafe { buffer.assume_init() }
    }

    /// Equivalent to `get`, but into a user-provided buffer instead
    /// of allocating. Panics if the buffer is not large enough.
    pub fn get_many_into<R>(&self, pe: PE, range: R, into: &mut [T], _ctx: &ShmemCtx)
    where
        R: RangeBounds<usize> + Clone,
    {
        let (start, end) = apply_range_bounds(range.clone(), self.as_ref());
        let buffer_size = end - start;
        assert!(
            into.len() >= buffer_size,
            "provided buffer was not large enough!"
        );
        // SAFETY: shbox is on the symmetric heap since, well, it's a shbox.
        //         we know buffer has enough capacity by the assert
        unsafe {
            shmem_getmem(
                into.as_mut_ptr() as *mut c_void,
                (self.as_ref() as *const [T] as *const T).offset(start as _) as *mut c_void,
                buffer_size * size_of::<T>(),
                pe.0 as _,
            )
        }
    }

    pub fn get_many_nbi<'s, R>(
        &'s self,
        range: R,
        pe: PE,
        _ctx: &ShmemCtx,
    ) -> PendingNbiSliceOp<'s, T>
    where
        R: RangeBounds<usize> + Clone,
    {
        let (start, end) = apply_range_bounds(range.clone(), self.as_ref());
        let buffer_size = end - start;
        // SAFETY: UnsafeCell<T> is transparent over T.
        let buffer: Box<UnsafeCell<[MaybeUninit<T>]>> =
            unsafe { transmute(Box::<[T]>::new_uninit_slice(buffer_size)) };
        unsafe {
            shmem_getmem_nbi(
                buffer.get() as *mut c_void,
                (self.as_ref() as *const [T] as *const T).offset(start as _) as *mut c_void,
                buffer_size * size_of::<T>(),
                pe.0 as _,
            )
        }
        unsafe { nbi_slice_op(buffer) }
    }

    pub fn get_single_nbi<'s>(
        &'s self,
        idx: usize,
        pe: PE,
        _ctx: &ShmemCtx,
    ) -> PendingNbiOp<'s, T> {
        assert!(
            idx < self.len(),
            "tried to idx out of bounds: len {}, idx {idx}",
            self.len()
        );
        let buffer = Box::new(UnsafeCell::new(MaybeUninit::uninit()));
        unsafe {
            shmem_getmem_nbi(
                buffer.get() as *mut c_void,
                (self.as_ref() as *const [T] as *const T).offset(idx as _) as *mut c_void,
                size_of::<T>(),
                pe.0 as _,
            )
        }
        unsafe { nbi_op(buffer) }
    }

    pub fn put_single_nbi<'s>(
        &'s mut self,
        idx: usize,
        data: &'s T,
        pe: PE,
        _ctx: &ShmemCtx,
    ) -> PendingNbiUnitOp<'s> {
        assert!(
            idx < self.len(),
            "tried to idx out of bounds: len {}, idx {idx}",
            self.len()
        );
        unsafe {
            shmem_putmem_nbi(
                (self.raw_ptr_mut() as *mut T).offset(idx as _) as *mut c_void,
                data as *const T as *const c_void,
                size_of::<T>(),
                pe.0 as _,
            );
        }
        nbi_noout_op()
    }

    pub fn put_many_nbi<'s>(
        &'s mut self,
        offset: usize,
        data: &'s [T],
        pe: PE,
        _ctx: &ShmemCtx,
    ) -> PendingNbiUnitOp<'s> {
        if data.len() + offset > self.len() {
            panic!("tried to write more data into a shbox than would fit!");
        }

        // SAFETY: shbox is on the symmetric heap by construction
        //         shbox has room for at laest data.len() elements,
        //         or we would've panicked
        unsafe {
            shmem_putmem_nbi(
                self.as_mut_ptr().offset(offset as _) as *mut c_void,
                data.as_ptr() as *const c_void,
                size_of::<T>() * data.len(),
                pe.0 as _,
            );
        }

        nbi_noout_op()
    }

    // TODO: currently, this means we just panic at runtime
    //       it'd be nice if we could find some way to ensure
    //       type-wise we have a rectangular array
    pub fn all_to_all_shbox(&self, nelems_per_pe: usize, ctx: &ShmemCtx) -> Self {
        assert_eq!(
            nelems_per_pe * ctx.n_pes(),
            self.len(),
            "len and nelems * pes mismatch in all_to_all!"
        );

        let shm = ctx.shmallocator();
        let mut shout: Box<[MaybeUninit<T>], _> =
            Box::new_uninit_slice_in(nelems_per_pe * ctx.n_pes(), &shm);

        unsafe {
            shmem_alltoallmem(
                *ctx.team().interpret_as::<shmem_team_t>(),
                shout.as_mut_ptr() as *mut c_void,
                self.as_ptr() as *const c_void,
                nelems_per_pe * size_of::<T>(),
            );
        }

        Shbox {
            // here we see a symptom of the shmallocator
            // this transmtue should be removable at some point
            // but we need either:
            // 1. shmalloc is copy
            // 2. stored ref to shmalloc
            internal: unsafe { transmute(shout) },
        }
    }

    pub fn all_to_all(&self, nelems_per_pe: usize, ctx: &ShmemCtx) -> Box<[T]> {
        assert_eq!(
            nelems_per_pe * ctx.n_pes(),
            self.len(),
            "len and nelems * pes mismatch in all_to_all!"
        );

        let shm = ctx.shmallocator();
        let mut shout: Box<[MaybeUninit<T>], _> =
            Box::new_uninit_slice_in(nelems_per_pe * ctx.n_pes(), &shm);

        unsafe {
            shmem_alltoallmem(
                *ctx.team().interpret_as::<shmem_team_t>(),
                shout.as_mut_ptr() as *mut c_void,
                self.as_ptr() as *const c_void,
                nelems_per_pe * size_of::<T>(),
            );
        }

        let mut lout = Box::new_uninit_slice(nelems_per_pe * ctx.n_pes());
        unsafe { std::ptr::copy_nonoverlapping(shout.as_ptr(), lout.as_mut_ptr(), nelems_per_pe * ctx.n_pes()); }
        unsafe { lout.assume_init() }
    }
}

impl<'ctx, T: ?Sized> Deref for Shbox<'ctx, T> {
    type Target = T;

    fn deref(&self) -> &T {
        self.internal.deref()
    }
}

impl<'ctx, T: ?Sized> DerefMut for Shbox<'ctx, T> {
    fn deref_mut(&mut self) -> &mut T {
        self.internal.deref_mut()
    }
}

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

// pub(crate) fn apply_range_bounds<R: RangeBounds<usize>, T>(bounds: R, t: &[T]) -> (usize, usize) {
//     let end = match bounds.end_bound() {
//         std::ops::Bound::Included(x) => *x,
//         std::ops::Bound::Excluded(x) => x.saturating_sub(1),
//         std::ops::Bound::Unbounded => t.len(),
//     };
//     let start = match bounds.start_bound() {
//         std::ops::Bound::Included(x) => *x,
//         std::ops::Bound::Excluded(x) => *x + 1,
//         std::ops::Bound::Unbounded => 0,
//     };
//     if end > t.len() {
//         panic!("end of range out of bounds: {end} > {}", t.len());
//     }
//     if start > t.len() {
//         panic!("start of range out of bounds: {end} > {}", t.len());
//     }
//     if start > end {
//         panic!("invalid range: start before end: {start}..{end}");
//     }
//     (start, end)
// }

pub fn apply_range_bounds<R: RangeBounds<usize>, T>(bounds: R, t: &[T]) -> (usize, usize) {
    let len = t.len();
    let start = match bounds.start_bound() {
        Bound::Included(&s) => s,
        Bound::Excluded(&s) => s.saturating_add(1),
        Bound::Unbounded => 0,
    };

    // Determine the end index based on the upper bound.
    let end = match bounds.end_bound() {
        Bound::Included(&e) => e.saturating_add(1),
        Bound::Excluded(&e) => e,
        Bound::Unbounded => len,
    };

    let end = end.min(len);
    let start = start.min(end);

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
                (self.into.internal.as_ref() as *const [T] as *const T).offset(start as _)
                    as *mut c_void,
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

unsafe impl<'ctx, T: AtomicFetch> Sync for Shbox<'ctx, Atomic<T>> {}

/// By construction, a reference to some memory on the symmetric heap.
#[derive(Debug, Copy, Clone)]
pub struct Shptr<R> {
    internal: R,
}

impl<R> AsRef<R> for Shptr<R> {
    fn as_ref(&self) -> &R {
        &self.internal
    }
}

impl<R> Deref for Shptr<R> {
    type Target = R;

    fn deref(&self) -> &Self::Target {
        &self.internal
    }
}

unsafe impl<T: AtomicFetch> Sync for Shptr<&Atomic<T>> {}

//impl<'ctx, T: AtomicFetch> AtomicFetch for Shptr<'ctx, Atomic<T>> {
//}
