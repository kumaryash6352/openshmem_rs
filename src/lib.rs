//! An ergonomic wrapper over the OpenSHMEM API.

// Since we're working with many enums
// from FFI, this comes up quite a bit.
#![allow(non_upper_case_globals)]
#![warn(
    clippy::undocumented_unsafe_blocks,
    missing_docs,
    clippy::missing_panics_doc,
    clippy::missing_errors_doc
)]
#![cfg_attr(
    feature = "shmalloc",
    feature(allocator_api, set_ptr_value, ptr_as_ref_unchecked)
)]

use std::{
    ffi::{c_char, c_void, CStr, CString},
    fmt::Display,
    marker::PhantomData, sync::Once,
};

use openshmem_sys::shmem::{
    shmem_addr_accessible, shmem_barrier_all, shmem_ctx_t, shmem_finalize, shmem_global_exit,
    shmem_impl_team_t, shmem_info_get_name, shmem_info_get_version, shmem_init, shmem_my_pe,
    shmem_n_pes, shmem_pe_accessible, shmem_ptr, shmem_team_config_t, shmem_team_my_pe,
    SHMEM_CMP_EQ, SHMEM_CMP_GE, SHMEM_CMP_GT, SHMEM_CMP_LE, SHMEM_CMP_LT, SHMEM_CMP_NE,
    SHMEM_MAX_NAME_LEN, SHMEM_TEAM_WORLD,
};

#[cfg(test)]
mod test;

pub use openshmem_sys::shmem as ffi;
mod macros;
#[cfg(feature = "shmalloc")]
use shmalloc::{PEReference, Shbox, Shmallocator};
use thiserror::Error;

static CTX_INITIALIZED: Once = Once::new();

// /// Get a reference to the global CTX,
// /// if already instantiated.
// pub fn ctx() -> Option<&'static ShmemCtx> {
//     CTX.get()
// }

// /// Convenience wrapper over `get`. Panics if
// /// the CTX has not been initialized.
// pub fn ctx_p() -> &'static ShmemCtx {
//     CTX.get().unwrap()
// }

/// Thin wrapper around a PE's u32 integer id that allows
/// for builder-pattern-esque remote PE
/// accesses.
///
/// Access the PE id by the first field.
#[derive(Debug, Clone, Copy)]
pub struct PE(pub u32);

impl PartialEq<usize> for PE {
    fn eq(&self, other: &usize) -> bool {
        self.0 as usize == *other
    }
}

impl Display for PE {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl PE {
    /// Return the raw PE idx.
    ///
    /// This is always safe to call.
    pub fn raw(&self) -> usize {
        self.0 as _
    }
}

impl std::ops::Deref for PE {
    type Target = u32;

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

/// General error type for OpenSHMEM functions.
#[derive(Debug, Error)]
pub enum ShmemError {
    /// The given reference was inaccessible from the
    /// remote PE.
    #[error("requested PE ({0}) inaccessible")]
    Inaccessible(PE),
    /// The ShmemCTX has already been initialized through another init call.
    #[error("already initialized shmem ctx")]
    AlreadyInitialized,
    /// The error given by the underlying implementation
    /// is not defined by the specification.
    #[error("implementation defined: {0}")]
    ImplementationDefined(i32),
}

/// The world Shmem CTX. Unlike it's specification-defined
/// counterpart, this is safe to instantiate multiple times.
///
/// Repeated instantiations will return an Error.
pub struct ShmemCtx {}

// TODO: ShmemCtx trait:
//       - ShmemCtx struct -> WorldCtx impl ShmemCtx
//       - TeamCtx -> impl ShmemCtx
/// A team's CTX. Tied to the lifetime of it's global CTX,
/// which is usually static anyway.
pub struct TeamCtx<'a> {
    _inner: shmem_ctx_t,
    _phantom: PhantomData<&'a ()>,
}

impl ShmemCtx {
    /// Unlike it's C counterpart, this is safe to call after initializing,
    /// however it will have no effect on a preexisting CTX.
    pub fn init() -> Result<ShmemCtx, ShmemError> {
        // Ok(CTX.get_or_init(|| {
        //     // SAFETY: If a CTX already exists, CTX would,
        //     //         well, exist. Therefore, the sanity
        //     //         check required by shmem_init is
        //     //         satisifed.
        //     unsafe { shmem_init() }

        //     ShmemCtx {}
        // }))
        if CTX_INITIALIZED.is_completed() {
            Err(ShmemError::AlreadyInitialized)
        } else {
            // SAFETY: We check to see if CTX_INITIALIZAED already.
            unsafe { shmem_init() }
            CTX_INITIALIZED.call_once(|| {});
            Ok(Self {})
        }
    }

    /// Returns the team this context refers to.
    pub fn team(&self) -> Handle<Team> {
        // TODO:
        Handle {
            ptr: unsafe { SHMEM_TEAM_WORLD as *mut c_void },
            _inner: PhantomData::default(),
        }
    }

    /// Equivalent to `shmem_my_pe`; returns the unique
    /// number representing the calling PE.
    pub fn my_pe(&self) -> PE {
        // SAFETY: Since we have a CTX, shmem_init has been called.
        //         By spec, the return value of shmem_n_pes mest be
        //         in [0..n_pes], which is representable by u32,
        //         unless we have n_pes > u32::MAX in which case well
        //         I don't really know what to do.
        unsafe { PE(shmem_my_pe() as _) }
    }

    /// Equivalent to `shmem_n_pes`; returns the
    /// amount of PEs in the known world.
    pub fn n_pes(&self) -> usize {
        // SAFETY: Since we have a CTX, shmem_init has been called.
        // TODO: SAFETY: Does this function actually emit
        //               negatives?
        unsafe { shmem_n_pes() as _ }
    }

    /// Equivalent to `shmem_finalize`.
    /// Equivalent to `ShmemCtx::drop`.
    pub fn finalize(self) {
        drop(self)
    }

    /// Equivalent to `shmem_global_exit`.
    ///
    /// Causes all PEs to exit with the given status code.
    /// If multiple PEs call this at roughly the same time,
    /// specification states all processes will exit with one
    /// of the given status codes.
    pub fn global_exit(&self, status: i32) -> ! {
        // SAFETY: Execution, by spec, does not leave this block.
        unsafe { shmem_global_exit(status) }
        unreachable!(
            "OpenSHMEM shmem_global_exit() has returned execution \
             to the caller. Please make a bug report to your \
             OpenSHMEM implementor about this!"
        );
    }

    /// Equivalent to `shmem_pe_accessible`.
    ///
    /// Checks if another PE exists in the world.
    pub fn pe_accessible(&self, pe: PE) -> bool {
        // SAFETY: Since we have a CTX, shmem_init has been called.
        // TODO: SAFETY: Is shmem_pe_accessible safe to pass invalid
        //               PEs to?
        unsafe { shmem_pe_accessible(pe.0 as _) != 0 }
    }

    /// Equivalent to `shmem_addr_accessible`.
    ///
    /// Checks if the given PTR exists on another PE.
    pub fn addr_accessible<T: ?Sized>(&self, ptr: *const T, pe: PE) -> bool {
        // SAFETY: Since we have a CTX, shmem_init has been called.
        // TODO: SAFETY: How do we even go about reasoning about
        //               whether a Rust-ptr is similar enough to
        //               a ptr-ptr?
        // TODO: SAFETY: What happens with fat ptrs?
        unsafe { shmem_addr_accessible(ptr as *const c_void, pe.0 as _) > 0 }
    }

    /// Equivalent to `shmem_ptr`.
    ///
    /// Safety considerations not currently known.
    pub unsafe fn try_ptr<T>(&self, dest: *mut T, pe: PE) -> Result<*mut T, ShmemError> {
        // TODO: SAFETY: Yeah I got no clue.
        //               This function might not even be able
        //               to exist safely.
        //               Until then, since it's sorta the point of
        //               OpenSHMEM, we just let it ride.
        let ptr = unsafe { shmem_ptr(dest as *const c_void, pe.0 as _) } as *mut T;
        Ok(ptr)
    }

    /// Equivalent to `shmem_info_get_version`.
    ///
    /// Returns the major and minor version of the
    /// SHMEM implementation, in that order.
    pub fn info_get_version(&self) -> (i32, i32) {
        let mut minor = 0;
        let mut major = 0;
        // SAFETY: Since we have a CTX, shmem_init has been called.
        //         We safely initialized minor and major, so they are valid
        //         even if meaningless.
        unsafe {
            shmem_info_get_version(&mut major as *mut i32, &mut minor as *mut i32);
        }
        (major, minor)
    }

    /// Equivalent to `shmem_info_get_name`.
    ///
    /// Returns the name of the underlying OpenSHMEM
    /// implementation.
    ///
    /// See `info_get_name_str` for a lossy version that
    /// returns a String instead of a CString.
    pub fn info_get_name(&self) -> CString {
        let mut raw = vec![0; SHMEM_MAX_NAME_LEN as usize + 1];
        // SAFETY: We know raw is a valid vector of at least SHMEM_MAX_NAME_LEN size
        //         because we reserved that much space.
        unsafe { shmem_info_get_name(raw.as_mut_ptr() as *mut c_char) };
        CStr::from_bytes_until_nul(&raw)
            .expect("shmem_info_get_name should provide NUL-terminated string!")
            .to_owned()
    }

    /// Almost equivalent to `shmem_info_get_name`.
    ///
    /// Returns the name of the underlying OpenSHMEM
    /// implementation.
    ///
    /// Drops whatever can't be parsed to UTF-8.
    ///
    pub fn info_get_name_str(&self) -> String {
        self.info_get_name().to_string_lossy().to_string()
    }

    /// Almost equivalent to `shmem_init_thread`.
    ///
    /// Unlike it's C counterpart, this is safe to call after initializing,
    /// however it with no effect on a preexisting CTX.
    ///
    /// # Panics
    /// When the OpenSHMEM implementation states an invalid ThreadLevel has
    /// been applied.
    // pub fn shmem_init_thread(
    //     requested: ThreadLevel,
    // ) -> Result<(Option<ThreadLevel>, &'static ShmemCtx), ShmemError> {
    //     let req_raw = requested as c_int;
    //     let mut actual_raw: c_int = 0;
    //     if CTX.get().is_none() {
    //         let res = unsafe { shmem_init_thread(req_raw, &mut actual_raw as *mut c_int) };
    //         if res == 0 {
    //             Err(ShmemError::ImplementationDefined(res))
    //         } else {
    //             let actual = ThreadLevel::try_from(actual_raw)
    //                 .expect("OpenSHMEM implementation should return known thread level!");
    //             Ok((
    //                 Some(actual),
    //                 CTX.get_or_init(|| {
    //                     // we have initialized the library by shmem_init_thread
    //                     ShmemCtx {}
    //                 }),
    //             ))
    //         }
    //     } else {
    //         Ok((None, CTX.get().unwrap()))
    //     }
    // }

    // /// Equivalent to `shmem_query_thread`.
    // ///
    // /// Returns the level of threading support that
    // /// the implementation decides on.
    // pub fn query_thread(&self) -> ThreadLevel {
    //     let mut out: c_int = 0;
    //     // SAFETY: Since we've a CTX, the library has been initialized.
    //     unsafe { shmem_query_thread(&mut out as *mut c_int) };
    //     out.try_into()
    //         .expect("OpenSHMEM implementation should return known thread level")
    // }

    /// Thin wrapper over `shmem_team_my_pe` that returns None instead of
    /// -1 if the team is invalid.
    pub fn team_my_pe<'ctx>(&'ctx self, team: Handle<'ctx, Team>) -> Option<PE> {
        // SAFETY: Since we've a CTX, the library has been initialized.
        //         We know this Handle must've been valid... at some point at least.
        let raw = unsafe { shmem_team_my_pe(team.ptr as *mut shmem_impl_team_t) };
        if raw == -1 {
            None
        } else {
            Some(PE(raw as _))
        }
    }

    /// Thin wrapper over `shmem_team_n_pes` that returns None instead of
    /// -1 if the team is invalid.
    pub fn team_n_pes<'a>(&'a self, team: Handle<'a, Team>) -> Option<PE> {
        // SAFETY: Since we've a CTX, the library has been initialized.
        let raw = unsafe { shmem_team_my_pe(team.ptr as _) };
        if raw == -1 {
            None
        } else {
            Some(PE(raw as _))
        }
    }

    /// Get a handle to a Shmallocator that allocates memory
    /// on the symmetric heap.
    #[cfg(feature = "shmalloc")]
    pub fn shmallocator<'s>(&'s self) -> Shmallocator<'s> {
        Shmallocator::from(self)
    }

    // COLLECTIVES

    /// Equivalent to `shmem_barrier_all`.
    ///
    /// Wait until ALL PEs reach this point.
    pub fn barrier_all(&self) {
        // SAFETY: We have a CTX, so shmem_init() has been called.
        unsafe { shmem_barrier_all() }
    }

    // TODO: reevaluate soundness wrappers for barrier*()
    //       issues:
    //          - is range including invalid pe an error? fine? unspecified?
    //            - what does sos do?
    //            - what does spec say?
    //          - is it sound to ask another team to barrier?
    //            - does this block caller pe if pe is on a diff team?
    //          - team handle

    // RMA
    /// Obtain a lifetimed reference to a remote PE.
    ///
    /// Useful for builder-style batched remote memory access.
    pub fn pe<'ctx>(&'ctx self, pe: usize) -> PEReference<'ctx> {
        assert!(
            self.pe_accessible(PE(pe as _)),
            "ctx.pe() called with invalid PE idx {pe}"
        );
        PEReference {
            ctx: self,
            pe: PE(pe as _),
        }
    }
}

// pub trait ShmemData: Pod + Clone {}

/// Thin wrapper over `shmem_team_config_t`.
///
/// Construct with `TeamConfig::new()`.
pub struct TeamConfig {
    _inner: shmem_team_config_t,
}

impl TeamConfig {
    /// Construct a new `TeamConfig` with the given `num_contexts`.
    pub fn new(num_contexts: usize) -> Self {
        Self {
            _inner: shmem_team_config_t {
                num_contexts: num_contexts as _,
            },
        }
    }
}

impl Drop for ShmemCtx {
    fn drop(&mut self) {
        // SAFETY: Since we are dropping THE only CTX
        //         in the program, there is no other
        //         safe way to call shmem routines.
        unsafe { shmem_finalize() }
    }
}

#[cfg(feature = "shmalloc")]
mod shmalloc {
    use std::{
        alloc::{AllocError, Allocator, Layout},
        ffi::c_void,
        fmt::Debug,
        mem::{self, MaybeUninit},
        ops::{Deref, DerefMut, RangeBounds},
        ptr::NonNull,
    };

    use bytemuck::Pod;
    use openshmem_sys::shmem::{
        shmem_align, shmem_calloc, shmem_free, shmem_getmem, shmem_putmem, shmem_realloc,
    };

    use crate::{ArithmeticReducible, Atomic, AtomicFetch, BooleanReducible, CompareReducible, ShmemCtx, PE};

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
            }
        }

        /// Constructs a shared mutable slice with at least `len` `f(usize)`'s.
        /// The parameter passed to `f` is the index being filled.
        ///
        /// Note that this type is technically unsound. I don't know how to fix that yet.
        pub fn array_gen<T>(
            &'ctx self,
            mut f: impl FnMut(usize) -> T,
            len: usize,
        ) -> Shbox<'ctx, [T]> {
            let mut vec = Box::new_zeroed_slice_in(len, self);
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
        pub fn array<T: Clone>(&'ctx self, t: T, len: usize) -> Shbox<'ctx, [T]> {
            let mut vec = Box::new_zeroed_slice_in(len, self);
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
        pub fn shbox<T>(&'ctx self, t: T) -> Shbox<'ctx, T> {
            Shbox {
                internal: Box::new_in(t, self),
            }
        }
    }

    pub struct Shbox<'ctx, T: ?Sized> {
        internal: Box<T, &'ctx Shmallocator<'ctx>>,
    }

    impl<'ctx, T: ?Sized> Shbox<'ctx, T> {
        pub fn raw(&self) -> &T {
            self.internal.as_ref()
        }

        pub fn raw_ptr(&self) -> *const T {
            self.internal.as_ref() as _
        }

        pub fn raw_ptr_mut(&mut self) -> *mut T {
            self.internal.as_mut() as _
        }
    }

    impl<'ctx, T: ArithmeticReducible> Shbox<'ctx, T> {
        pub fn reduce_sum(&mut self, ctx: &ShmemCtx) {
            unsafe { T::sum_into(self, ctx) }
        }
        pub fn reduce_prod(&mut self, ctx: &ShmemCtx) {
            unsafe { T::prod_into(self, ctx) }
        }
    }
    impl<'ctx, T: BooleanReducible> Shbox<'ctx, T> {
        pub fn reduce_and(&mut self, ctx: &ShmemCtx) {
            unsafe { T::and_into(self, ctx) }
        }
        pub fn reduce_or(&mut self, ctx: &ShmemCtx) {
            unsafe { T::or_into(self, ctx) }
        }
        pub fn reduce_xor(&mut self, ctx: &ShmemCtx) {
            unsafe { T::xor_into(self, ctx) }
        }
    }
    impl<'ctx, T: CompareReducible> Shbox<'ctx, T> {
        pub fn reduce_max(&mut self, ctx: &ShmemCtx) {
            unsafe { T::max_into(self, ctx) }
        }
        pub fn reduce_min(&mut self, ctx: &ShmemCtx) {
            unsafe { T::min_into(self, ctx) }
        }
    }

    impl<'ctx, T: ArithmeticReducible> Shbox<'ctx, [T]> {
        pub fn reduce_sum(&mut self, elements: usize, ctx: &ShmemCtx) {
            unsafe { T::sum_into_many(self, elements, ctx) }
        }
        pub fn reduce_prod(&mut self, elements: usize, ctx: &ShmemCtx) {
            unsafe { T::prod_into_many(self, elements, ctx) }
        }
    }
    impl<'ctx, T: BooleanReducible> Shbox<'ctx, [T]> {
        pub fn reduce_and(&mut self, elements: usize, ctx: &ShmemCtx) {
            unsafe { T::and_into_many(self, elements, ctx) }
        }
        pub fn reduce_or(&mut self, elements: usize, ctx: &ShmemCtx) {
            unsafe { T::or_into_many(self, elements, ctx) }
        }
        pub fn reduce_xor(&mut self, elements: usize, ctx: &ShmemCtx) {
            unsafe { T::xor_into_many(self, elements, ctx) }
        }
    }
    impl<'ctx, T: CompareReducible> Shbox<'ctx, [T]> {
        pub fn reduce_max(&mut self, elements: usize, ctx: &ShmemCtx) {
            unsafe { T::max_into_many(self, elements, ctx) }
        }
        pub fn reduce_min(&mut self, elements: usize, ctx: &ShmemCtx) {
            unsafe { T::min_into_many(self, elements, ctx) }
        }
    }

    impl<'ctx, T: AtomicFetch> Shbox<'ctx, Atomic<T>> {}

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

    fn apply_range_bounds<R: RangeBounds<usize>, T>(bounds: R, t: &[T]) -> (usize, usize) {
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
                    (self.into.as_ref() as *const [T] as *const T).offset(start as _)
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
        pub fn finish(self) {
            drop(self)
        }
    }

    /// Reference to a remote PE, wrapped for convenient usage
    /// of RMA routines.
    #[derive(Copy, Clone)]
    pub struct PEReference<'ctx> {
        pub(crate) ctx: &'ctx ShmemCtx,
        pub(crate) pe: PE,
    }

    impl<'ctx> PEReference<'ctx> {
        #[cfg(feature = "rma")]
        /// Edit an object on a remote PE directly.
        ///
        /// Uses `shmem_ptr` to perform one-sided memory manipulation.
        pub fn get_direct<T: ?Sized>(self, what: &mut Shbox<T>, action: impl FnOnce(&mut T)) {
            let ptr = what.internal.as_mut() as *mut T as *mut () as usize;
            if self.ctx.addr_accessible(ptr as *const c_void, PE(self.pe)) {
                // SAFETY: Since the RMA feature is activated, this will not be null.
                //         As a Shbox, the Shbox is valid so long as we have a reference to it.
                //         As a PEReference, we know the PE asked for exists by construction.
                let remote_ptr =
                    unsafe { shmem_ptr(ptr as *const c_void, self.pe as _) } as *mut c_void;
                // PANIC: If the remote ptr is null, the platform does not support RMA, which
                //        shouldn't happen since feature = "rma".
                // SAFETY: ptr::as_mut prevents us from dereferencing a null ptr.
                //         ptr::with_metadata_of ensures we have valid ptr metadata (in this case, len.)
                //         as a remote shbox,
                action(unsafe {
                    remote_ptr
                        .with_metadata_of(what.internal.as_mut() as *mut T)
                        .as_mut()
                        .expect("shmem_ptr returned null, but shmem_addr_accessible returned true. \
                                 your OpenSHMEM impl may not support RMA. please open an issue if you know it does.")
                });
            } else {
                #[cfg(debug_assertions)]
                panic!("addr not accessible on remote PE, despite being a Shbox!");
                #[cfg(not(debug_assertions))]
                unreachable!("addr is shbox, and therefore must be on a remote pe.");
            }
        }

        /// Obtain a MUTABLE slice into a remote PE's Shbox'd array.
        ///
        /// Note that the data in the slice is a copy of the LOCAL SHBOX's array at
        /// that point. TODO: I dunno what to do about that.
        pub fn write<'a, 'shbox, R, T>(
            &self,
            shbox: &'shbox mut Shbox<'ctx, [T]>,
            range: R,
        ) -> MutableArrayView<'ctx, 'shbox, T, R>
        where
            'ctx: 'shbox,
            T: Pod,
            R: RangeBounds<usize> + Clone,
        {
            let buffer_size = {
                let (start, end) = apply_range_bounds(range.clone(), shbox);
                end - start + 1
            };
            MutableArrayView {
                _ctx: &self.ctx,
                into: shbox,
                range: range.clone(),
                on: self.pe,
                buf: unsafe { Box::new_uninit_slice(buffer_size).assume_init() },
            }
        }

        pub fn read<'shbox, R, T>(&self, shbox: &'shbox Shbox<'ctx, [T]>, range: R) -> Box<[T]>
        where
            'ctx: 'shbox,
            T: Pod,
            R: RangeBounds<usize> + Clone,
        {
            let (start, end) = apply_range_bounds(range.clone(), shbox);
            let buffer_size = end - start + 1;
            let mut buffer: Box<[MaybeUninit<T>]> = Box::new_uninit_slice(buffer_size);
            // SAFETY: shbox is on the symmetric heap since, well, it's a shbox.
            //         we know buffer has enough capacity since we derived n_elems
            //         from the range asked
            unsafe {
                shmem_getmem(
                    buffer.as_mut_ptr() as *mut c_void,
                    (shbox.as_ref() as *const [T] as *const T).offset(start as _) as *mut c_void,
                    buffer_size * size_of::<T>(),
                    self.pe.0 as _,
                )
            }
            // SAFETY: T is Pod, and so any bit representation is a valid T.
            //         Therefore, even if we read data unset by shmem_getmem,
            //         we read valid T's.
            unsafe { mem::transmute(buffer) }
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
}

/// Marker for Handles to a Team.
#[derive(Clone, Copy)]
pub struct Team;

/// Handles are like references that are opaque to the user.
#[derive(Clone)]
pub struct Handle<'ctx, T> {
    ptr: *mut c_void,
    _inner: PhantomData<&'ctx T>,
}

impl<'ctx, T> Handle<'ctx, T> {
    /// Functionally, handle interpretation.
    pub unsafe fn interpret_as<E: Sized>(&self) -> &E {
        &*(self.ptr as *const E)
    }

    /// Obtain a raw pointer to whatever this handle refers to.
    pub fn raw(&self) -> *mut c_void {
        self.ptr
    }
}

// /// Equivalent to it's OpenSHMEM definition:
// /// support for usage of SHMEM routines from other threads.
// #[repr(C)]
// #[derive(Debug, Copy, Clone)]
// pub enum ThreadLevel {
//     /// Only one thread may call routines.
//     ThreadSingle = shmem_thread_levels_SHMEM_THREAD_SINGLE as _,
//     /// All threads may call routines, but effects are done on the main thread.
//     ThreadFunneled = shmem_thread_levels_SHMEM_THREAD_FUNNELED as _,
//     /// All threads may call routines, but effects are observed sequentially.
//     ThreadSerialized = shmem_thread_levels_SHMEM_THREAD_SERIALIZED as _,
//     /// All threads may call routines.
//     ThreadMultiple = shmem_thread_levels_SHMEM_THREAD_MULTIPLE as _,
// }

// impl TryFrom<c_int> for ThreadLevel {
//     type Error = ();

//     fn try_from(value: c_int) -> Result<Self, Self::Error> {
//         match value as u32 {
//             shmem_thread_levels_SHMEM_THREAD_SINGLE => Ok(ThreadLevel::ThreadSingle),
//             shmem_thread_levels_SHMEM_THREAD_FUNNELED => Ok(ThreadLevel::ThreadFunneled),
//             shmem_thread_levels_SHMEM_THREAD_SERIALIZED => Ok(ThreadLevel::ThreadSerialized),
//             shmem_thread_levels_SHMEM_THREAD_MULTIPLE => Ok(ThreadLevel::ThreadMultiple),
//             _ => Err(()),
//         }
//     }
// }

/// Represents types that have a `shmem_[and, or, xor]_reduce`.
///
/// See `Shbox` for safe wrappers of these methods.
#[diagnostic::on_unimplemented(
    message = "no OpenSHMEM routine for boolean reductions into {Self}",
    label = "this {Self} here",
    note = "OpenSHMEM provides boolean reduction routines for [i/u][8, 16, 32, 64, size]"
)]
pub trait BooleanReducible: Sized {
    /// Apply `shmem_[typename]_and_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn and_into(shbox: &mut Shbox<'_, Self>, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_and_reduce`.
    ///
    /// # Safety
    /// `n` must be less than or equal to the number of elements in shbox.
    unsafe fn and_into_many(shbox: &mut Shbox<'_, [Self]>, n: usize, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_or_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn or_into(shbox: &mut Shbox<'_, Self>, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_or_reduce`.
    ///
    /// # Safety
    /// `n` must be less than or equal to the number of elements in shbox.
    unsafe fn or_into_many(shbox: &mut Shbox<'_, [Self]>, n: usize, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_xor_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn xor_into(shbox: &mut Shbox<'_, Self>, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_xor_reduce`.
    ///
    /// # Safety
    /// `n` must be less than or equal to the number of elements in shbox.
    unsafe fn xor_into_many(shbox: &mut Shbox<'_, [Self]>, n: usize, ctx: &ShmemCtx);
}
/// Represents types that have a `shmem_[sum, prod]_reduce`.
///
/// See `Shbox` for safe wrappers of these methods.
#[diagnostic::on_unimplemented(
    message = "no OpenSHMEM routine for arithmetic reductions into {Self}",
    label = "this {Self} here",
    note = "OpenSHMEM provides arithmetic reduction routines for [i/u][8, 16, 32, 64, size], f[32, 64]"
)]
pub trait ArithmeticReducible: Sized {
    /// Apply `shmem_[typename]_sum_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn sum_into(shbox: &mut Shbox<'_, Self>, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_sum_reduce`.
    ///
    /// # Safety
    /// `n` must be less than or equal to the number of elements in shbox.
    unsafe fn sum_into_many(shbox: &mut Shbox<'_, [Self]>, n: usize, ctx: &ShmemCtx);

    /// Apply `shmem_[typename]_prod_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn prod_into(shbox: &mut Shbox<'_, Self>, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_prod_reduce`.
    ///
    /// # Safety
    /// `n` must be less than or equal to the number of elements in shbox.
    unsafe fn prod_into_many(shbox: &mut Shbox<'_, [Self]>, n: usize, ctx: &ShmemCtx);
}
/// Represents types that have a `shmem_[max, min]_reduce`.
///
/// See `Shbox` for safe wrappers of these methods.
#[diagnostic::on_unimplemented(
    message = "no OpenSHMEM routine for max/min reductions into {Self}",
    label = "this {Self} here",
    note = "OpenSHMEM provides max/min reduction routines for [i/u][8, 16, 32, 64, size], f[32, 64]"
)]
pub trait CompareReducible: Sized {
    /// Apply `shmem_[typename]_max_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn max_into(shbox: &mut Shbox<'_, Self>, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_max_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn max_into_many(shbox: &mut Shbox<'_, [Self]>, n: usize, ctx: &ShmemCtx);

    /// Apply `shmem_[typename]_min_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn min_into(shbox: &mut Shbox<'_, Self>, ctx: &ShmemCtx);
    /// Apply `shmem_[typename]_min_reduce`.
    ///
    /// # Safety
    /// TODO:
    unsafe fn min_into_many(shbox: &mut Shbox<'_, [Self]>, n: usize, ctx: &ShmemCtx);
}

impl_arithmetic_reducible!(u8, uint8);
impl_arithmetic_reducible!(i8, int8);
impl_arithmetic_reducible!(u16, uint16);
impl_arithmetic_reducible!(i16, int16);
impl_arithmetic_reducible!(u32, uint32);
impl_arithmetic_reducible!(i32, int32);
impl_arithmetic_reducible!(u64, uint64);
impl_arithmetic_reducible!(i64, int64);
impl_arithmetic_reducible!(f32, float);
impl_arithmetic_reducible!(f64, double);
impl_arithmetic_reducible!(usize, size);

impl_compare_reducible!(u8, uint8);
impl_compare_reducible!(i8, int8);
impl_compare_reducible!(u16, uint16);
impl_compare_reducible!(i16, int16);
impl_compare_reducible!(u32, uint32);
impl_compare_reducible!(i32, int32);
impl_compare_reducible!(u64, uint64);
impl_compare_reducible!(i64, int64);
impl_compare_reducible!(f32, float);
impl_compare_reducible!(f64, double);
impl_compare_reducible!(usize, size);

impl_boolean_reducible!(u8, uint8);
impl_boolean_reducible!(i8, int8);
impl_boolean_reducible!(u16, uint16);
impl_boolean_reducible!(i16, int16);
impl_boolean_reducible!(u32, uint32);
impl_boolean_reducible!(i32, int32);
impl_boolean_reducible!(u64, uint64);
impl_boolean_reducible!(i64, int64);
impl_boolean_reducible!(usize, size);

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

// TODO: `FakeAtomic[32/64]`: uses associated int32/64 routines
//                               to atomically edit a datatype.
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
