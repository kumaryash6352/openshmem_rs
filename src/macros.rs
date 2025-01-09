/// Implement ArithmeticReducible for a type that has
/// reduction routines in the SHMEM spec.
/// Usage: `impl_arithmetic_reducible(rust_type_name, shmem_type_name)`
/// Example: `impl_arithmetic_reducible(u8, uchar)`
#[macro_export]
macro_rules! impl_arithmetic_reducible {
    ($type:ty, $typename:ident) => {
        ::paste::paste! {
            impl ArithmeticReducible for $type {
                unsafe fn sum_into(shbox: &mut Shbox<'_, $type>, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _sum_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             1);
                }
                unsafe fn prod_into(shbox: &mut Shbox<'_, $type>, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _prod_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             1);
                }

                unsafe fn sum_into_many(shbox: &mut Shbox<'_, [$type]>, n: usize, _ctx: &ShmemCtx) {
                    assert!(shbox.len() >= n);
                    ::openshmem_sys::shmem::[<shmem_ $typename _sum_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             n);
                }
                unsafe fn prod_into_many(shbox: &mut Shbox<'_, [$type]>, n: usize, _ctx: &ShmemCtx) {
                    assert!(shbox.len() >= n);
                    ::openshmem_sys::shmem::[<shmem_ $typename _prod_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             n);
                }
            }
        }
    };
}

/// Implement BooleanReducible for a type that has
/// reduction routines in the SHMEM spec.
/// Usage: `impl_boolean_reducible(rust_type_name, shmem_type_name)`
/// Example: `impl_boolean_reducible(u8, uchar)`
#[macro_export]
macro_rules! impl_boolean_reducible {
    ($type:ty, $typename:ident) => {
        ::paste::paste! {
            impl BooleanReducible for $type {
                unsafe fn and_into(shbox: &mut Shbox<'_, $type>, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _and_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             1);
                }
                unsafe fn or_into(shbox: &mut Shbox<'_, $type>, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _or_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                            shbox.raw_ptr_mut(),
                                                                            shbox.raw_ptr_mut(),
                                                                            1);
                }
                unsafe fn xor_into(shbox: &mut Shbox<'_, $type>, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _xor_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut(),
                                                                             shbox.raw_ptr_mut(),
                                                                             1);
                }
                unsafe fn and_into_many(shbox: &mut Shbox<'_, [$type]>, n: usize, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _and_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             n);
                }
                unsafe fn or_into_many(shbox: &mut Shbox<'_, [$type]>, n: usize, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _or_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                            shbox.raw_ptr_mut() as *mut _,
                                                                            shbox.raw_ptr_mut() as *mut _,
                                                                            n);
                }
                unsafe fn xor_into_many(shbox: &mut Shbox<'_, [$type]>, n: usize, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _xor_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             n);
                }
            }
        }
    };
}

/// Implement CompareReducible for a type that has
/// reduction routines in the SHMEM spec.
/// Usage: `impl_compare_reducible(rust_type_name, shmem_type_name)`
/// Example: `impl_compare_reducible(u8, uchar)`
#[macro_export]
macro_rules! impl_compare_reducible {
    ($type:ty, $typename:ident) => {
        ::paste::paste! {
            impl CompareReducible for $type {
                unsafe fn max_into(shbox: &mut Shbox<'_, $type>, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _max_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut(),
                                                                             shbox.raw_ptr_mut(),
                                                                             1);
                }
                unsafe fn min_into(shbox: &mut Shbox<'_, $type>, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _min_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut(),
                                                                             shbox.raw_ptr_mut(),
                                                                             1);
                }
                unsafe fn max_into_many(shbox: &mut Shbox<'_, [$type]>, n: usize, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _max_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             n);
                }
                unsafe fn min_into_many(shbox: &mut Shbox<'_, [$type]>, n: usize, _ctx: &ShmemCtx) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _min_reduce>](::openshmem_sys::shmem::SHMEM_TEAM_WORLD,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             shbox.raw_ptr_mut() as *mut _,
                                                                             n);
                }
            }
        }
    };
}

/// Implement Waitable for a type that has
/// wait_until routines in the SHMEM spec.
/// Usage: `impl_waitable(rust_type_name, shmem_type_name)`
/// Example: `impl_waitable(u8, uchar)`
#[macro_export]
macro_rules! impl_waitable {
    ($type:ty, $typename:ident) => {
        ::paste::paste! {
            impl Waitable for $type {
                unsafe fn wait_until(shbox: &mut Shbox<'_, Self>, op: ShmemCompareOp, x: $type) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _wait_until>](shbox.raw_ptr_mut(),
                                                                             op as _,
                                                                             x);
                }
                unsafe fn wait_until_all(shbox: &mut Shbox<'_, [Self]>, op: ShmemCompareOp, x: $type) {
                    ::openshmem_sys::shmem::[<shmem_ $typename _wait_until_all>](shbox.raw_ptr_mut() as _,
                                                                                 shbox.len(),
                                                                                 ::std::ptr::null(),
                                                                                 op as _,
                                                                                 x);

                }
                unsafe fn wait_until_some(shbox: &mut Shbox<'_, [Self]>, op: ShmemCompareOp, x: $type) -> Vec<usize> {
                    let mut idxs = vec![0; shbox.len()];
                    let n = ::openshmem_sys::shmem::[<shmem_ $typename _wait_until_some>](shbox.raw_ptr_mut() as _,
                                                                                          shbox.len(),
                                                                                          idxs.as_mut_ptr(),
                                                                                          ::std::ptr::null(),
                                                                                          op as _,
                                                                                          x);
                    idxs.truncate(n);
                    idxs
                }
                unsafe fn wait_until_any(shbox: &mut Shbox<'_, [Self]>, op: ShmemCompareOp, x: $type) -> usize {
                    ::openshmem_sys::shmem::[<shmem_ $typename _wait_until_any>](shbox.raw_ptr_mut() as _,
                                                                                 shbox.len(),
                                                                                 ::std::ptr::null(),
                                                                                 op as _,
                                                                                 x) as usize
                }
            }
        }
    };
}

/// Implement AtomicFetch for a type that has
/// fetch/set/swap routines in the SHMEM spec.
/// Usage: `impl_atomic_fetch(rust_type_name, shmem_type_name)`
/// Example: `impl_atomic_fetch(u8, uchar)`
#[macro_export]
macro_rules! impl_atomic_fetch {
    ($type:ty, $typename:ident) => {
        ::paste::paste! {
            impl AtomicFetch for $type {
                fn atomic_fetch(shbox: &Shbox<'_, Atomic<Self>>, from: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_fetch>](shbox.raw_ptr() as *const $type,
                                                                                        from.raw() as _) }
                }
                fn atomic_set(shbox: &Shbox<'_, Atomic<Self>>, new: $type, to: PE, _ctx: &ShmemCtx) {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_set>](shbox.raw_ptr() as *mut $type,
                                                                                      new,
                                                                                      to.raw() as _); }
                }
                fn atomic_swap(shbox: &Shbox<'_, Atomic<Self>>, with: $type, to: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_swap>](shbox.raw_ptr() as *mut $type,
                                                                                       with,
                                                                                       to.raw() as _) }
                }
            }
        }
    };
}

/// Implement AtomicInt for a type that has
/// [fetch_]compare_swap/inc/addroutines in the SHMEM spec.
/// Usage: `impl_atomic_int(rust_type_name, shmem_type_name)`
/// Example: `impl_atomic_int(u32, uint32)`
#[macro_export]
macro_rules! impl_atomic_int {
    ($type:ty, $typename:ident) => {
        ::paste::paste! {
            impl AtomicInt for $type {
                fn atomic_compare_swap(shbox: &Shbox<'_, Atomic<$type>>, if_equals: $type, then_set_to: $type, on: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_compare_swap>](shbox.get_cell_ptr() as *mut $type,
                                                                                               if_equals,
                                                                                               then_set_to,
                                                                                               on.raw() as _) }
                }
                fn atomic_fetch_inc(shbox: &Shbox<'_, Atomic<$type>>, from: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_fetch_inc>](shbox.get_cell_ptr() as *mut $type,
                                                                                            from.raw() as _) }
                }
                fn atomic_inc(shbox: &Shbox<'_, Atomic<$type>>, to: PE, _ctx: &ShmemCtx) {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_inc>](shbox.get_cell_ptr() as *mut $type,
                                                                                      to.raw() as _); }
                }
                fn atomic_fetch_add(shbox: &Shbox<'_, Atomic<$type>>, plus: $type, from: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_fetch_add>](shbox.get_cell_ptr() as *mut $type,
                                                                                            plus,
                                                                                            from.raw() as _) }
                }
                fn atomic_add(shbox: &Shbox<'_, Atomic<$type>>, plus: $type, to: PE, _ctx: &ShmemCtx) {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_add>](shbox.get_cell_ptr() as *mut $type,
                                                                                      plus,
                                                                                      to.raw() as _); }
                }
            }
        }
    };
}

/// Implement AtomicInt for a type that has
/// [fetch_]compare_swap/inc/addroutines in the SHMEM spec.
/// Usage: `impl_atomic_int(rust_type_name, shmem_type_name)`
/// Example: `impl_atomic_int(u32, uint32)`
#[macro_export]
macro_rules! impl_atomic_bit {
    ($type:ty, $typename:ident) => {
        ::paste::paste! {
            impl AtomicBitwise for $type {
                fn atomic_fetch_and(shbox: &Shbox<'_, Atomic<$type>>, with: $type, from: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_fetch_and>](shbox.get_cell_ptr() as *mut $type as *mut _,
                                                                                            with as _,
                                                                                            from.raw() as _) as _ }
                }
                fn atomic_and(shbox: &Shbox<'_, Atomic<$type>>, with: $type, to: PE, _ctx: &ShmemCtx) {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_and>](shbox.get_cell_ptr() as *mut $type as *mut _,
                                                                                      with as _,
                                                                                      to.raw() as _); }
                }
                fn atomic_fetch_or(shbox: &Shbox<'_, Atomic<$type>>, with: $type, from: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_fetch_or>](shbox.get_cell_ptr() as *mut $type as *mut _,
                                                                                            with as _,
                                                                                            from.raw() as _) as _ }
                }
                fn atomic_or(shbox: &Shbox<'_, Atomic<$type>>, with: $type, to: PE, _ctx: &ShmemCtx) {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_or>](shbox.get_cell_ptr() as *mut $type as *mut _,
                                                                                      with as _,
                                                                                      to.raw() as _); }
                }
                fn atomic_fetch_xor(shbox: &Shbox<'_, Atomic<$type>>, with: $type, from: PE, _ctx: &ShmemCtx) -> $type {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_fetch_xor>](shbox.get_cell_ptr() as *mut $type as *mut _,
                                                                                            with as _,
                                                                                            from.raw() as _) as _ }
                }
                fn atomic_xor(shbox: &Shbox<'_, Atomic<$type>>, with: $type, to: PE, _ctx: &ShmemCtx) {
                    unsafe { ::openshmem_sys::shmem::[<shmem_ $typename _atomic_xor>](shbox.get_cell_ptr() as *mut $type as *mut _,
                                                                                      with as _,
                                                                                      to.raw() as _); }
                }
            }
        }
    };
}


// from https://users.rust-lang.org/t/ensure-that-struct-t-has-size-n-at-compile-time/61108/2
// TODO: use this to implement AssertAtomic[32/64]
/// Assert at compile time that a type has a given size.
#[macro_export]
macro_rules! assert_size_eq {
    ($type:ty, $size:expr) => {
        ::paste::paste! {
            const _: [(); size] = [(); ::std::mem::size_of::<$type>()];
        }
    };
}
