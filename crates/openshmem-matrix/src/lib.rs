use std::{collections::HashMap, fmt::Debug, ops::Range};

use rayon::prelude::*;

use openshmem_rs::{
    shmalloc::{Shbox, Shmallocator},
    ShmemCtx, PE, traits::Shend
};
use openshmem_vec::{Shvec, WouldRealloc};

#[cfg(feature = "debug")]
macro_rules! dprintln {
    ($($arg:tt)*) => {
        println!($($arg)*)
    };
}
#[cfg(not(feature = "debug"))]
macro_rules! dprintln {
    ($($arg:tt)*) => {{}};
}

/// We use this in ONE function.
/// TODO: See if Rust will ever get support for ie. Result<(), RowOnDifferentPe | WouldRealloc>
#[derive(Debug)]
pub enum Either<L: Debug, R: Debug> {
    L(L),
    R(R),
}

#[derive(Debug)]
pub struct RowOnDifferentPe;

pub struct CrsMatrix<'ctx, T: Shend + Clone> {
    /// Rows in the matrix. By construction, identical across all PEs.
    rows: usize,
    /// Cols in the matrix. By construction, identical across all PEs.
    cols: usize,
    /// PEs in context at time of construction.
    pes: usize,
    /// Maximum rows tracked by a given PE.
    rows_per_pe: usize,
    /// Cached value of `self.ctx.my_pe().raw()`.
    mpe: usize,
    ctx: &'ctx ShmemCtx,
    shm: &'ctx Shmallocator<'ctx>,
    /// Column of each element in `xs`. `col_idxs.len() == xs.len()`.
    col_idxs: Shvec<'ctx, usize>,
    /// Value of each element in the matrix. `col_idxs.len() == xs.len()`.
    xs: Shvec<'ctx, T>,
    /// The elements of the Nth row (zero-indexed) are row_ptrs[N]..row_ptrs[N + 1], which may be a zero-length slice.
    row_ptrs: Shbox<'ctx, [usize]>,
}

impl<'ctx, T: Shend + Send + Copy + std::fmt::Debug> CrsMatrix<'ctx, T> {
    pub fn new(
        rows: usize,
        cols: usize,
        ctx: &'ctx ShmemCtx,
        shm: &'ctx openshmem_rs::shmalloc::Shmallocator<'ctx>,
    ) -> Self {
        dprintln!(
            "[PE {:>2}]: creating new CrsMatrix with {} rows, {} cols",
            ctx.my_pe().raw(),
            rows,
            cols
        );
        let rows_per_pe = rows.div_ceil(ctx.n_pes());
        let initial_capacity = rows * 2;
        let row_ptrs = shm.array(0, rows_per_pe + 1);
        let mpe = ctx.my_pe().raw();

        Self {
            rows,
            cols,
            ctx,
            shm,
            rows_per_pe,
            mpe,
            row_ptrs,
            pes: ctx.n_pes(),
            col_idxs: Shvec::new(ctx, shm, initial_capacity),
            xs: Shvec::new(ctx, shm, initial_capacity),
        }
    }

    /// Given a row, return the PE the row belongs on and the index into row_ptrs for that row.
    pub fn global_row_to_pe_row(&self, row: usize) -> (usize, PE) {
        self.assert_row_in_bounds(row);
        (row / self.pes, PE((row % self.pes) as _))
    }

    pub fn row_on_this_pe(&self, row: usize) -> bool {
        row % self.pes == self.mpe
    }

    fn assert_row_in_bounds(&self, row: usize) {
        assert!(
            row < self.rows,
            "given row {row} out of bounds for {}x{} matrix",
            self.rows,
            self.cols
        );
    }

    pub fn cols_on_row(&self, row: usize) -> Box<[usize]> {
        let (idx, remote_pe) = self.global_row_to_pe_row(row);
        let (start, end) = self.ctx.quiet((
            self.row_ptrs.get_single_nbi(idx, remote_pe, self.ctx),
            self.row_ptrs.get_single_nbi(idx + 1, remote_pe, self.ctx),
        ));
        if start == end {
            Box::default()
        } else {
            self.col_idxs.span_remote(start..end, remote_pe)
        }
    }

    pub fn nnz_on_row(&self, row: usize) -> usize {
        let (idx, remote_pe) = self.global_row_to_pe_row(row);
        let (start, end) = self.ctx.quiet((
            self.row_ptrs.get_single_nbi(idx, remote_pe, self.ctx),
            self.row_ptrs.get_single_nbi(idx + 1, remote_pe, self.ctx),
        ));
        end - start
    }

    pub fn xs_on_row(&self, row: usize) -> Box<[T]> {
        let (idx, remote_pe) = self.global_row_to_pe_row(row);
        let (start, end) = self.ctx.quiet((
            self.row_ptrs.get_single_nbi(idx, remote_pe, self.ctx),
            self.row_ptrs.get_single_nbi(idx + 1, remote_pe, self.ctx),
        ));
        if start == end {
            Box::default()
        } else {
            self.xs.span_remote(start..end, remote_pe)
        }
    }

    pub fn nnz(&self) -> usize {
        let mut res = self.shm.shbox(self.xs.len());
        res.reduce_sum(self.ctx);
        *res
    }

    pub fn put(
        &mut self,
        row: usize,
        col: usize,
        value: T,
    ) -> Result<(), Either<RowOnDifferentPe, WouldRealloc>> {
        let (row_idx, target_pe) = self.global_row_to_pe_row(row);
        if target_pe != self.mpe {
            return Err(Either::L(RowOnDifferentPe));
        };

        let (start, end) = (self.row_ptrs[row_idx], self.row_ptrs[row_idx + 1]);
        match self.col_idxs.span(start..end).binary_search(&col) {
            Ok(replace_at) => self.xs.replace(start + replace_at, value),
            Err(insert_at) => {
                self.xs
                    .insert(start + insert_at, value)
                    .map_err(Either::R)?;
                self.col_idxs
                    .insert(start + insert_at, col)
                    .map_err(Either::R)?;
                self.row_ptrs[(row_idx + 1)..]
                    .iter_mut()
                    .for_each(|r| *r += 1);
            }
        }
        Ok(())
    }

    pub fn get(&self, row: usize, col: usize) -> Option<T> {
        let (row_idx, target_pe) = self.global_row_to_pe_row(row);
        if target_pe == self.mpe {
            // local read
            let (start, end) = (self.row_ptrs[row_idx], self.row_ptrs[row_idx + 1]);
            self.col_idxs
                .span(start..end)
                .binary_search(&col)
                .ok()
                .map(|lidx| {
                    self.xs
                        .index(start + lidx)
                        .expect("element in col_idxs to  have corresponding xs element")
                })
        } else {
            let (start, end) = self.ctx.quiet((
                self.row_ptrs.get_single_nbi(row_idx, target_pe, self.ctx),
                self.row_ptrs
                    .get_single_nbi(row_idx + 1, target_pe, self.ctx),
            ));
            let col_idxs = if start == end {
                Box::default()
            } else {
                self.col_idxs.span_remote(start..end, target_pe)
            };
            col_idxs.binary_search(&col).ok().map(|lidx| {
                self.xs
                    .index_remote(start + lidx, target_pe)
                    .expect("remote element in col_idxs to have corresponding remote xs element")
            })
        }
    }

    pub fn from_coo(
        rows: usize,
        cols: usize,
        xs: &[(usize, usize, T)],
        ctx: &'ctx ShmemCtx,
        shm: &'ctx openshmem_rs::shmalloc::Shmallocator<'ctx>,
    ) -> Self {
        let npes = ctx.n_pes();
        let mpe = ctx.my_pe().raw();
        let to_pe = |row| row % npes;
        // step 1: get data to respective PEs
        let avg_cap = xs.len().div_ceil(npes);
        let mut outboxes = (0..ctx.n_pes())
            .map(|_| Vec::with_capacity(avg_cap))
            .collect::<Vec<_>>();
        for (row, col, x) in xs {
            let remote_pe = to_pe(*row);
            outboxes[remote_pe].push((*row, *col, *x));
        }
        let mut my_incoming = Vec::new();
        //dprintln!("[PE {:>2}] outboxes: {outboxes:?}", self.ctx.my_pe(),);
        for pe in 0..npes {
            let outgoing = Shvec::from_iter(ctx, shm, outboxes[pe].iter().copied());
            dprintln!(
                "[PE {:>2}] sending to pe {pe}: {:?}",
                self.ctx.my_pe(),
                &outgoing.span(..)
            );
            if pe == mpe {
                for rpe in 0..npes {
                    let mut remote = outgoing.span_remote(.., PE(rpe as _));
                    dprintln!("[PE {:>2}] took {remote:?} from pe {rpe}", self.ctx.my_pe());
                    my_incoming.extend_from_slice(remote.as_mut());
                }
            }
            ctx.barrier_all();
        }
        // now, my_incoming has every value we care about
        // sort by "insertion" order
        my_incoming.par_sort_by_cached_key(|(r, c, _x)| r * rows + c);
        // eliminate collisions
        // TODO: doc that if for coords x, y there are more than one (x, y, c) in xs, c can be any one given
        my_incoming.dedup_by_key(|(r, c, _x)| *r * rows + *c);

        // now, my_incoming is optimized for insertion order
        // split to SoA
        let (irows, (icols, ixs)): (Vec<usize>, (Vec<usize>, Vec<T>)) =
            my_incoming.into_iter().map(|(r, c, x)| (r, (c, x))).unzip();
        assert!(irows.len() == icols.len()); // let the compiler know we can be aggro with unrolling
        assert!(icols.len() == ixs.len());

        // col_idxs and xs are actually fine as-is since we sorted them
        let xs = Shvec::from_iter(ctx, shm, ixs);
        let col_idxs = Shvec::from_iter(ctx, shm, icols);

        // row_idxs is the complicated part
        let rows_per_pe = rows.div_ceil(ctx.n_pes());
        let mut row_ptrs = shm.array_default(rows_per_pe + 1);

        let mut current_row = row_ptrs[0];
        for (k, row) in irows.into_iter().enumerate() {
            let row = row / npes;
            while current_row < row {
                current_row += 1;
                row_ptrs[current_row] = k;
            }
        }

        Self {
            rows,
            cols,
            pes: ctx.n_pes(),
            rows_per_pe,
            mpe,
            ctx,
            shm,
            col_idxs,
            xs,
            row_ptrs,
        }
    }

    // pub fn put_from_coo_all(&mut self, xs: &[(usize, usize, T)]) -> Result<(), RowOnDifferentPe> {
    //     let mut rows = HashMap::new();
    //     for (row, col, t) in xs {
    //         let (row_idx, pe) = self.global_row_to_pe_row(*row);
    //         if pe != self.mpe {
    //             return Err(RowOnDifferentPe);
    //         };
    //         rows.entry(row_idx)
    //             .or_insert_with(|| {
    //                 self.cols_on_row(*row)
    //                     .iter()
    //                     .copied()
    //                     .zip(self.xs_on_row(*row).iter().copied())
    //                     .collect::<Vec<_>>()
    //             })
    //             .push((*col, t.clone()));
    //     }

    //     rows.values_mut().for_each(|vs| vs.sort_unstable_by_key(|(c, _x)| *c));
    //     rows.values_mut().for_each(|vs| vs.dedup_by_key(|(c, _x)| *c));

    //     let min_cap = xs.len() + self.xs.capacity();
    //     self.xs.grow_to(min_cap);
    //     self.col_idxs.grow_to(min_cap);

    //     for (row_idx, row_data) in rows {
    //         let shift_amt = row_data.len();
    //         let o_start = self.row_ptrs[row_idx];
    //         let o_end = self.row_ptrs[row_idx + 1];
    //         let o_len = o_end - o_start;
    //         let n_end = o_start + shift_amt;
    //         self.xs.shift_right(, o_end, shift_amt);
    //         // first, shift all elements in col_idxs, etc. foward

    //         // for (col, t) in row_data {
    //         //     match self.col_idxs.span(start..end).binary_search(&col) {
    //         //         Ok(replace_at) => self.xs.replace(start + replace_at, t),
    //         //         Err(insert_at) => {
    //         //             self.xs
    //         //                 .insert(start + insert_at, t.clone())
    //         //                 .expect("we allocated enough earlier");
    //         //             self.col_idxs
    //         //                 .insert(start + insert_at, col)
    //         //                 .expect("we allocated enough earlier");
    //         //             self.row_ptrs[(row_idx + 1)..]
    //         //                 .iter_mut()
    //         //                 .for_each(|r| *r += 1);
    //         //         }
    //         //     }
    //         // }
    //     }
    //     Ok(())
    // }

    pub fn put_many_all(&mut self, xs: &[(usize, usize, T)]) {
        // step 1: get each data point to their respective pe
        let avg_cap = xs.len().div_ceil(self.ctx.n_pes());
        let mut outboxes = (0..self.ctx.n_pes())
            .map(|_| Vec::with_capacity(avg_cap))
            .collect::<Vec<_>>();
        for (row, col, x) in xs {
            let (_remote_row_idx, remote_pe) = self.global_row_to_pe_row(*row);
            outboxes[remote_pe.raw()].push((*row, *col, *x));
        }
        let mut my_incoming = Vec::new();
        //dprintln!("[PE {:>2}] outboxes: {outboxes:?}", self.ctx.my_pe(),);
        for pe in 0..self.ctx.n_pes() {
            let outgoing = Shvec::from_iter(self.ctx, self.shm, outboxes[pe].iter().copied());
            dprintln!(
                "[PE {:>2}] sending to pe {pe}: {:?}",
                self.ctx.my_pe(),
                &outgoing.span(..)
            );
            if pe == self.ctx.my_pe().raw() {
                for rpe in 0..self.ctx.n_pes() {
                    let mut remote = outgoing.span_remote(.., PE(rpe as _));
                    dprintln!("[PE {:>2}] took {remote:?} from pe {rpe}", self.ctx.my_pe());
                    my_incoming.extend_from_slice(remote.as_mut());
                }
            }
            self.ctx.barrier_all();
        }

        // TODO step 2: filter out values we don't care about

        // step 3: allocate space
        let mut buf = self.shm.shbox(self.col_idxs.len() + my_incoming.len());
        buf.reduce_sum(self.ctx);
        self.col_idxs.grow_to(*buf);
        *buf = self.xs.len() + my_incoming.len(); // might be unnecessary
        buf.reduce_sum(self.ctx);
        self.xs.grow_to(*buf);

        // TODO: preemptively and smartly insert rather than just insert
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
        my_incoming.par_sort_unstable_by_key(|(r, c, _t)| r * self.rows + c);
        my_incoming.dedup_by_key(|(r, c, _t)| *r * self.rows + *c);
        let n = my_incoming.len() as f32;
        dprintln!("[PE {:>2}] incoming: {:?}", self.ctx.my_pe(), my_incoming);
        todo!("there used to be logic here, but it got removed when from_coo. todo: rewrite using from_coo");
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
    matrix.put(mpe, mpe * 2 + 1, mpe).unwrap();
    matrix.put(mpe, mpe * 2, mpe).unwrap();

    println!("row_ptrs = {:?}", &matrix.row_ptrs[..5]);
    println!("row_ptrs.len() = {}", matrix.row_ptrs.len());
    println!("col_idxs = {:?}", matrix.col_idxs.span(..));
    println!("xs = {:?}", matrix.xs.span(..));

    ctx.barrier_all();
    assert_eq!(matrix.nnz(), ctx.n_pes() * 2);
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

    let my_xs =
        (0..8)
            .map(|i| (i * mpe, i * mpe * 2, i))
            .map(|(r, c, t)| (r % 64, c % 64, t))
            .collect::<Vec<_>>();
    let m2 = CrsMatrix::from_coo(64, 64, &my_xs, &ctx, &shm);

    println!("row_ptrs = {:?}", &m2.row_ptrs[..5]);
    println!("row_ptrs.len() = {}", m2.row_ptrs.len());
    println!("col_idxs = {:?}", m2.col_idxs.span(..));
    println!("xs = {:?}", m2.xs.span(..));
}
