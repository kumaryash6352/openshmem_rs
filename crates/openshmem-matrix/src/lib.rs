use openshmem_rs::{
    shmalloc::{Shbox, Shmallocator},
    Pod, ShmemCtx, PE,
};
use openshmem_vec::Shvec;

#[derive(Debug)]
pub struct RowOnDifferentPe;

pub struct CrsMatrix<'ctx, T: Pod + Clone> {
    rows: usize,
    rows_per_pe: usize,
    pes: usize,
    cols: usize,
    ctx: &'ctx ShmemCtx,
    shm: &'ctx Shmallocator<'ctx>,
    // col idxs for all rows, flat
    col_idxs: Shvec<'ctx, usize>,
    xs: Shvec<'ctx, T>,
    // start idx of each row in col_indices
    row_ptrs: Shbox<'ctx, [usize]>,
}

impl<'ctx, T: Pod + Clone + std::fmt::Debug> CrsMatrix<'ctx, T> {
    pub fn new(
        rows: usize,
        cols: usize,
        ctx: &'ctx ShmemCtx,
        shm: &'ctx openshmem_rs::shmalloc::Shmallocator<'ctx>,
    ) -> Self {
        println!(
            "[PE {:>2}]: creating new CrsMatrix with {} rows, {} cols",
            ctx.my_pe().raw(),
            rows,
            cols
        );
        let initial_capacity = rows * 2;
        let row_ptrs = shm.array(usize::MAX, rows + 1);

        Self {
            rows,
            cols,
            ctx,
            shm,
            row_ptrs,
            rows_per_pe: rows.div_ceil(ctx.n_pes()),
            pes: ctx.n_pes(),
            col_idxs: Shvec::new(ctx, shm, initial_capacity),
            xs: Shvec::new(ctx, shm, initial_capacity),
        }
    }

    pub fn global_row_to_pe_row(&self, row: usize) -> Option<(usize, PE)> {
        if row < self.rows {
            Some((row / self.pes, PE((row % self.pes) as _)))
        } else {
            None
        }
    }

    pub fn nnz(&self) -> usize {
        let mut res = self.shm.shbox(self.xs.len());
        res.reduce_sum(self.ctx);
        *res
    }

    pub fn put(&mut self, row: usize, col: usize, value: T) -> Result<(), RowOnDifferentPe> {
        assert!(
            row < self.rows && col < self.cols,
            "put at {row}, {col} out of bounds for {}x{} matrix",
            self.rows,
            self.cols
        );
        let (row_idx, target_pe) = self.global_row_to_pe_row(row).unwrap();
        if target_pe == self.ctx.my_pe() {
            println!("[PE {:>2}] local put: {row}, {col}", self.ctx.my_pe());
            let mut row_start = self.row_ptrs[row_idx];
            let row_end = self.row_ptrs[row_idx + 1];
            if row_start == usize::MAX {
                self.row_ptrs[row_idx] = self.col_idxs.len();
                row_start = self.col_idxs.len();
            }
            let col_idxs = self.col_idxs.span(row_start..row_end);
            match col_idxs.binary_search(&col) {
                Ok(at) => self.xs.replace(col_idxs[at], value),
                Err(should_be_at) => {
                    println!("[PE {:>2}] local put: self.cols_idxs = {:?}", self.ctx.my_pe(), self.col_idxs.span(..));
                    println!("[PE {:>2}] local put: inserting into self.cols_idxs @ {should_be_at}", self.ctx.my_pe());
                    // update col_idxs with the idx we're about to insert
                    self.col_idxs.insert(should_be_at, col).unwrap();
                    // offset future row ptrs by one
                    self.row_ptrs[(row_idx + 1)..]
                        .iter_mut()
                        .filter(|x| **x != usize::MAX)
                        .for_each(|x| *x += 1);
                    self.xs.insert(should_be_at, value).unwrap();
                }
            }
            Ok(())
        } else {
            Err(RowOnDifferentPe)
        }
    }

    pub fn get(&self, row: usize, col: usize) -> Option<T> {
        assert!(
            row < self.rows && col < self.cols,
            "put at {row}, {col} out of bounds for {}x{} matrix",
            self.rows,
            self.cols
        );
        let (row_idx, target_pe) = self.global_row_to_pe_row(row).unwrap();
        println!("[PE {:>2}] xs: {:?}", self.ctx.my_pe(), self.xs.span(..));
        println!("[PE {:>2}] row_idxs: {:?}", self.ctx.my_pe(), &self.row_ptrs[0..=0]);
        println!("[PE {:>2}] col_idxs: {:?}", self.ctx.my_pe(), self.col_idxs.span(..));
        if target_pe == self.ctx.my_pe() {
            println!("[PE {:>2}] local get: {row}, {col}", self.ctx.my_pe());
            let row_start = self.row_ptrs[row_idx];
            let row_end = self.row_ptrs[row_idx + 1];
            if row_start == usize::MAX {
                println!("[PE {:>2}] get bail: row not in array", self.ctx.my_pe());
                return None;
            }
            let col_idxs = self.col_idxs.span(row_start..row_end);
            println!("[PE {:>2}] local get: row_start = {}, col_idxs = {:?}", self.ctx.my_pe(), row_start, col_idxs);
            col_idxs
                .binary_search(&col)
                .inspect_err(|at|
                             println!("[PE {:>2}] local get bail: search didn't find col, col = {col}, at = {at}", self.ctx.my_pe())
                )
                .ok()
                .map(|at| self.xs.index_unwrap(at))
        } else {
            println!("[PE {:>2}] remote get: {row}, {col} on PE {:?}", self.ctx.my_pe(), target_pe);
            let (row_start, row_end) = self.ctx.quiet((
                self.row_ptrs.get_single_nbi(row_idx, target_pe, self.ctx),
                self.row_ptrs.get_single_nbi(row_idx + 1, target_pe, self.ctx),
            ));
            if row_start == usize::MAX {
                println!("[PE {:>2}] remote get bail: row not in array", self.ctx.my_pe());
                return None;
            }
            let col_idxs = self.col_idxs.span_remote(row_start..row_end, target_pe);
            println!("[PE {:>2}] remote get: row_start = {}, col_idxs = {:?}", self.ctx.my_pe(), row_start, col_idxs);
            col_idxs
                .binary_search(&col)
                .inspect_err(|_|
                             println!("[PE {:>2}] remote get bail: search didn't find col", self.ctx.my_pe())
                )
                .ok()
                .and_then(|at| self.xs.index_remote(at, target_pe))
        }
    }
}

pub fn main() {
    let ctx = ShmemCtx::init().unwrap();
    let shm = ctx.shmallocator();
    let rows = 4096;
    let cols = 4096;
    let mut matrix = CrsMatrix::new(rows, cols, &ctx, &shm);

    let mpe = ctx.my_pe().raw();
    matrix.put(mpe, mpe * 2, mpe).unwrap();

    ctx.barrier_all();
    assert_eq!(matrix.nnz(), ctx.n_pes());
    for i in 0..ctx.n_pes() {
        // FIXME: we expect each of these to return some value, since each pe N set N, 2N so something
        assert_eq!(
            matrix.get(i, i * 2),
            Some(i),
            "[PE {:>2}] failed verify at {i}, {}",
            ctx.my_pe().raw(),
            i * 2
        );
        ctx.barrier_all();
    }
}
