use crate::{impl_arithmetic_reducible, impl_boolean_reducible, impl_compare_reducible, shmalloc::Shbox, ShmemCtx};

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
