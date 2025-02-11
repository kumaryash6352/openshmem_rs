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
#![feature(allocator_api, set_ptr_value, ptr_as_ref_unchecked)]

use crate::shmalloc::{apply_range_bounds, MutableArrayView, Shbox, Shmallocator};
use bytemuck::{Pod, Zeroable};
use nbi::{nbi_op, nbi_slice_op, NbiOp, PendingNbiOp, PendingNbiSliceOp};
use std::{
    cell::UnsafeCell,
    ffi::{c_char, c_void, CStr, CString},
    fmt::Display,
    marker::PhantomData,
    mem::{self, transmute, MaybeUninit},
    ops::RangeBounds,
    sync::Once,
};

use openshmem_sys::shmem::{
    shmem_addr_accessible, shmem_barrier_all, shmem_collectmem, shmem_ctx_t, shmem_finalize,
    shmem_getmem, shmem_getmem_nbi, shmem_global_exit, shmem_impl_team_t, shmem_info_get_name,
    shmem_info_get_version, shmem_init, shmem_my_pe, shmem_n_pes, shmem_pe_accessible, shmem_ptr,
    shmem_putmem, shmem_quiet, shmem_team_config_t, shmem_team_my_pe, SHMEM_MAX_NAME_LEN,
    SHMEM_TEAM_WORLD,
};

#[cfg(test)]
mod test;

mod macros;
use thiserror::Error;

pub use openshmem_sys::shmem as ffi;
pub mod atomics;
pub mod nbi;
pub mod reduce;
pub mod shmalloc;
pub mod shmutex;
pub mod wait;

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
            // TODO: check build time of all binaries, log error if they don't match
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

    /// Finalize pending NBI operations.
    ///
    /// Common things that implement NbiOp:
    /// 1. `PendingNbi[Slice]Op`
    /// 2. `Vec<NbiOp>`
    /// 3. Tuples of `NbiOp`
    ///
    /// Equivalent to `shmem_quiet`.
    pub fn quiet<Nbis>(&self, nbis: Nbis) -> Nbis::Output
    where
        Nbis: NbiOp,
    {
        // SAFETY: We have initialized the library since we've a context.
        unsafe {
            shmem_quiet();
            nbis.after_quiet()
        }
    }

    /// Construct an array containing all elements in `from`
    /// across all involved PEs.
    ///
    /// Equivalent to `shmem_collect`.
    pub fn collect<T>(&self, from: &Shbox<'_, [T]>) -> Box<[T]> {
        let shm = self.shmallocator();
        let mut total_buffer_size = shm.shbox(from.len());
        total_buffer_size.reduce_sum(&self);
        let mut buf: Box<[MaybeUninit<T>]> = Box::new_uninit_slice(*total_buffer_size);

        // SAFETY: By construction, `from` is on the symmetric heap.
        //         We created `buf` with enough storage for all PEs elements.
        unsafe {
            shmem_collectmem(
                SHMEM_TEAM_WORLD,
                buf.as_mut_ptr() as *mut c_void,
                from.as_ptr() as *const c_void,
                *total_buffer_size * size_of::<T>(),
            );
        }

        // SAFETY: `shmem_collect` has copied `total_buffer_size`.
        unsafe { transmute(buf) }
    }
}

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

    /// Instantly replace the first `data.len()` elements of `shbox @ PE`
    /// with the elements from `data`.
    ///
    /// # Panics
    /// If `data.len() > shbox.len()`, panic.
    pub fn write_from<'shbox, T>(&self, shbox: &'shbox mut Shbox<'ctx, [T]>, data: &[T])
    where
        'ctx: 'shbox,
        T: Pod,
    {
        if data.len() > shbox.len() {
            panic!("tried to write more data into a shbox than would fit!");
        }

        // SAFETY: shbox is on the symmetric heap by construction
        //         shbox has room for at laest data.len() elements,
        //         or we would've panicked
        unsafe {
            shmem_putmem(
                shbox.as_mut_ptr() as *mut c_void,
                data.as_ptr() as *const c_void,
                size_of::<T>() * data.len(),
                self.pe.0 as _,
            );
        }
    }

    /// Alias to `read`.
    pub fn get<'shbox, R, T>(&self, shbox: &'shbox Shbox<'ctx, [T]>, range: R) -> Box<[T]>
    where
        'ctx: 'shbox,
        T: Pod,
        R: RangeBounds<usize> + Clone,
    {
        self.read(shbox, range)
    }

    /// Reads a slice from the `Shbox` on another PE.
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

    /// Equivalent to `read`, but into a user-provided buffer instead
    /// of allocating. Panics if the buffer is not large enough.
    pub fn read_into<'shbox, R, T>(&self, shbox: &'shbox Shbox<'ctx, [T]>, range: R, into: &mut [T])
    where
        'ctx: 'shbox,
        T: Pod,
        R: RangeBounds<usize> + Clone,
    {
        let (start, end) = apply_range_bounds(range.clone(), shbox);
        let buffer_size = end - start + 1;
        assert!(
            into.len() >= buffer_size,
            "provided buffer was not large enough!"
        );
        // SAFETY: shbox is on the symmetric heap since, well, it's a shbox.
        //         we know buffer has enough capacity by the assert
        unsafe {
            shmem_getmem(
                into.as_mut_ptr() as *mut c_void,
                (shbox.as_ref() as *const [T] as *const T).offset(start as _) as *mut c_void,
                buffer_size * size_of::<T>(),
                self.pe.0 as _,
            )
        }
    }

    pub fn read_nbi<'shbox, R, T>(
        &self,
        shbox: &'shbox Shbox<'ctx, [T]>,
        range: R,
    ) -> PendingNbiSliceOp<'shbox, T>
    where
        'ctx: 'shbox,
        T: Pod,
        R: RangeBounds<usize> + Clone,
    {
        let (start, end) = apply_range_bounds(range.clone(), shbox);
        let buffer_size = end - start + 1;
        // SAFETY: UnsafeCell<T> is transparent over T.
        let buffer: Box<UnsafeCell<[MaybeUninit<T>]>> =
            unsafe { transmute(Box::<[T]>::new_uninit_slice(buffer_size)) };
        unsafe {
            shmem_getmem_nbi(
                buffer.get() as *mut c_void,
                (shbox.as_ref() as *const [T] as *const T).offset(start as _) as *mut c_void,
                buffer_size * size_of::<T>(),
                self.pe.0 as _,
            )
        }
        unsafe { nbi_slice_op(buffer) }
    }

    pub fn get_single_nbi<'shbox, T>(
        &self,
        shbox: &Shbox<'shbox, [T]>,
        idx: usize,
    ) -> PendingNbiOp<'shbox, T>
    where
        T: Pod,
    {
        assert!(
            idx < shbox.len(),
            "tried to idx out of bounds: len {}, idx {idx}",
            shbox.len()
        );
        let buffer = Box::new(UnsafeCell::new(MaybeUninit::uninit()));
        unsafe {
            shmem_getmem_nbi(
                buffer.get() as *mut c_void,
                (shbox.as_ref() as *const [T] as *const T).offset(idx as _) as *mut c_void,
                size_of::<T>(),
                self.pe.0 as _,
            )
        }
        unsafe { nbi_op(buffer) }
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
