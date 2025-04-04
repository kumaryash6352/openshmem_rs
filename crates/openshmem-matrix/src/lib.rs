use openshmem_rs::{
    shmalloc::{Shbox, Shmallocator},
    Pod, ShmemCtx, Zeroable, PE,
};
use openshmem_vec::Shvec;

#[derive(Debug)]
pub struct RowOnDifferentPe;

pub struct CrsMatrix<'ctx, T: Pod + Clone> {
    rows: usize,
    cols: usize,
    pes: usize,
    ctx: &'ctx ShmemCtx,
    shm: &'ctx Shmallocator<'ctx>,
    // col idxs for all rows, flat
    col_idxs: Shvec<'ctx, usize>,
    xs: Shvec<'ctx, T>,
    // start idx of each row in col_indices
    row_ptrs: Shbox<'ctx, [usize]>,
}

impl<'ctx, T: Zeroable + Copy + std::fmt::Debug + Pod> CrsMatrix<'ctx, T> {
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
                    println!(
                        "[PE {:>2}] local put: self.cols_idxs = {:?}",
                        self.ctx.my_pe(),
                        self.col_idxs.span(..)
                    );
                    println!(
                        "[PE {:>2}] local put: inserting into self.cols_idxs @ {should_be_at}",
                        self.ctx.my_pe()
                    );
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
        println!(
            "[PE {:>2}] row_idxs: {:?}",
            self.ctx.my_pe(),
            &self.row_ptrs[0..=0]
        );
        println!(
            "[PE {:>2}] col_idxs: {:?}",
            self.ctx.my_pe(),
            self.col_idxs.span(..)
        );
        if target_pe == self.ctx.my_pe() {
            println!("[PE {:>2}] local get: {row}, {col}", self.ctx.my_pe());
            let row_start = self.row_ptrs[row_idx];
            let row_end = self.row_ptrs[row_idx + 1];
            if row_start == usize::MAX {
                println!("[PE {:>2}] get bail: row not in array", self.ctx.my_pe());
                return None;
            }
            let col_idxs = self.col_idxs.span(row_start..row_end);
            println!(
                "[PE {:>2}] local get: row_start = {}, col_idxs = {:?}",
                self.ctx.my_pe(),
                row_start,
                col_idxs
            );
            col_idxs
                .binary_search(&col)
                .inspect_err(|at| {
                    println!(
                        "[PE {:>2}] local get bail: search didn't find col, col = {col}, at = {at}",
                        self.ctx.my_pe()
                    )
                })
                .ok()
                .map(|at| self.xs.index_unwrap(at))
        } else {
            println!(
                "[PE {:>2}] remote get: {row}, {col} on PE {:?}",
                self.ctx.my_pe(),
                target_pe
            );
            let (row_start, row_end) = self.ctx.quiet((
                self.row_ptrs.get_single_nbi(row_idx, target_pe, self.ctx),
                self.row_ptrs
                    .get_single_nbi(row_idx + 1, target_pe, self.ctx),
            ));
            if row_start == usize::MAX {
                println!(
                    "[PE {:>2}] remote get bail: row not in array",
                    self.ctx.my_pe()
                );
                return None;
            }
            let col_idxs = self.col_idxs.span_remote(row_start..row_end, target_pe);
            println!(
                "[PE {:>2}] remote get: row_start = {}, col_idxs = {:?}",
                self.ctx.my_pe(),
                row_start,
                col_idxs
            );
            col_idxs
                .binary_search(&col)
                .inspect_err(|_| {
                    println!(
                        "[PE {:>2}] remote get bail: search didn't find col",
                        self.ctx.my_pe()
                    )
                })
                .ok()
                .and_then(|at| self.xs.index_remote(at, target_pe))
        }
    }

    pub fn put_many_all(&mut self, xs: &[(usize, usize, T)]) {
        // step 1: get each data point to their respective pe
        // let mut outboxes = (0..self.ctx.n_pes()).map(|_| Vec::new()).collect::<Vec<_>>();
        // for (row, col, x) in xs {
        //     let (remote_row_idx, remote_pe) = self.global_row_to_pe_row(*row).expect("row out of range");
        //     outboxes[remote_pe.raw()].push((remote_row_idx, col, x));
        // }
        // let mut n_incoming = self.shm.shbox(0);
        // for pe in 0..self.ctx.n_pes() {
        //     *n_incoming = outboxes[pe].len();
        //     n_incoming.reduce_and(self.ctx);
        //     let mut incoming =
        // }
        // scratch that, collect
        let xs = Shvec::from_iter(self.ctx, self.shm, xs.iter().cloned());
        xs.collect();

        // step 2: filter out values we don't care about
        let my_pe = self.ctx.my_pe();
        let mut xs = xs
            .iter()
            .map(|(r, c, x)| (self.global_row_to_pe_row(r).unwrap(), c, x))
            .filter(|((_row_idx, pe), _c, _x)| *pe == my_pe)
            .map(|((row_idx, _), c, x)| (row_idx, c, x))
            .collect::<Vec<_>>();
        xs.sort_by_key(|(r, c, _x)| r * self.cols + c);

        // step 3: allocate space
        let mut buf = self.shm.shbox(self.col_idxs.len() + xs.len());
        buf.reduce_sum(self.ctx);
        self.col_idxs.grow_to(*buf);
        *buf = self.xs.len() + xs.len(); // might be unnecessary
        buf.reduce_sum(self.ctx);
        self.xs.grow_to(*buf);

        // TODO: preemptively and smartly insert rather than just insert
        // // step 3.1: if we don't have anything to add, we're done
        // if xs.len() == 0 {
        //     return;
        // }

        // // step 4: TODO preemptively make groups and spaces for values where relevant
        // let mut insert_queues = Vec::<(usize, usize, &[(usize, usize, T)])>::new();
        // let mut start_group = 0;
        // for i in 0..xs.len() {
        //     if xs[i].0 == xs[start_group].0 { continue; }
        //     // we hit a new row; make space for start_group..(i + len(start_group))
        //     self.xs.shift_right(T::zeroed(), self.row_ptrs[xs[i].0], i - start_group).unwrap();
        //     self.col_idxs.shift_right(usize::MAX, self.row_ptrs[xs[i].0], i - start_group).unwrap();
        //     // push row_ptrs idx, xs/col_idxs overwrite starting index, data
        //     insert_queues.push((xs[start_group].0, self.row_ptrs[xs[i].0] - (i - start_group), &xs[start_group..i]));
        //     start_group = i;
        // }
        let n_pes = self.ctx.n_pes();
        for (row_idx, col, x) in xs {
            self.put(row_idx * n_pes, col, x).unwrap()
        }
        self.ctx.barrier_all();
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
