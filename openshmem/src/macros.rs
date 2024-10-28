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
