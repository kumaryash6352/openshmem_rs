use std::ops::Range;

use openshmem_rs::{
    shmalloc::{Shbox, Shmallocator},
    Pod, ShmemCtx, Zeroable, PE,
};
use openshmem_vec::Shvec;

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

#[derive(Debug)]
pub struct RowOnDifferentPe;

pub struct CrsMatrix<'ctx, T: Pod + Clone> {
    rows: usize,
    cols: usize,
    pes: usize,
    mpe: usize,
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
        dprintln!(
            "[PE {:>2}]: creating new CrsMatrix with {} rows, {} cols",
            ctx.my_pe().raw(),
            rows,
            cols
        );
        let initial_capacity = rows * 2;
        let row_ptrs = shm.array(usize::MAX, rows + 1);
        let mpe = ctx.my_pe().raw();

        Self {
            rows,
            cols,
            ctx,
            shm,
            mpe,
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

    pub fn row_on_this_pe(&self, row: usize) -> bool {
        row % self.pes == self.mpe
    }

    pub fn cols_on_row(&self, row: usize) -> Option<&[usize]> {
        if row >= self.rows {
            panic!("given row out of boudns")
        } else {
            let bounds = self.row_to_col_idxs_range(row);
            let start = bounds.0?;
            if let Some(e) = bounds.1 {
                Some(self.col_idxs.span(start..e))
            } else {
                Some(self.col_idxs.span(start..))
            }
        }
    }

    pub fn nnz_on_row(&self, row: usize) -> Option<&[T]> {
        if row >= self.rows {
            panic!("given row out of boudns")
        } else {
            let bounds = self.row_to_col_idxs_range(row);
            let start = bounds.0?;
            if let Some(e) = bounds.1 {
                Some(self.xs.span(start..e))
            } else {
                Some(self.xs.span(start..))
            }
        }
    }

    fn row_to_col_idxs_range(&self, row: usize) -> (Option<usize>, Option<usize>) {
        if row >= self.rows {
            panic!("given row out of boudns")
        } else {
            let start = self.row_ptrs.get(row).filter(|x| **x != usize::MAX).copied();
            let end = self
                .row_ptrs
                .iter()
                .skip(row + 1)
                .filter(|x| **x != usize::MAX)
                .next()
                .copied();
            (start, end)
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
            "[PE {:>2}] put at {row}, {col} out of bounds for {}x{} matrix",
            self.mpe,
            self.rows,
            self.cols
        );
        let (row_idx, target_pe) = self.global_row_to_pe_row(row).unwrap();
        if target_pe == self.mpe {
            let (mstart, mend) = self.row_to_col_idxs_range(row);
            dprintln!("[PE {:>2}] put: mstart, mend = {mstart:?}, {mend:?}", self.ctx.my_pe());
            if let Some(start) = mstart {
                // row is not empty
                dprintln!("[PE {:>2}] put: found start of row col_idx[{start}]", self.ctx.my_pe());
                let end = mend.unwrap_or(self.col_idxs.len());
                match self.col_idxs.span(start..end).binary_search(&col) {
                    Ok(at) => self.xs.replace(at, value),
                    Err(should_be_at) => {
                        let insert_at = start + should_be_at;
                        self.xs.insert(insert_at, value);
                        self.col_idxs.insert(insert_at, col);
                        self.row_ptrs[(row + 1)..].iter_mut().filter(|x| **x != usize::MAX).for_each(|x| *x += 1);
                    }
                }
                Ok(())
            } else {
                // row is empty
                let insert_at = mend.unwrap_or(self.xs.len());
                self.xs.insert(insert_at, value);
                self.col_idxs.insert(insert_at, col);
                self.row_ptrs[row] = insert_at;
                self.row_ptrs[(row + 1)..].iter_mut().filter(|x| **x != usize::MAX).for_each(|x| *x += 1);
                Ok(())
            }
        //     dprintln!("[PE {:>2}] local put: {row}, {col}", self.ctx.my_pe());
        //     let mut row_start = self.row_ptrs[row_idx];
        //     let row_end = self.row_ptrs[row_idx + 1];
        //     // dprintln!("[PE {:>2}] row_start..row_end = {row_start}..{row_end}", self.ctx.my_pe());
        //     // dprintln!("[PE {:>2}] self.row_idxs[..] = {:?}", self.ctx.my_pe(), &self.row_ptrs[..]);
        //     if row_start == usize::MAX {
        //         // find last initialized row
        //         let mut last_inited = 0;
        //         for rowi in (0..row_idx).rev() {
        //             if self.row_ptrs[rowi] != usize::MAX {
        //                 last_inited = rowi;
        //                 break;
        //             }
        //         }
        //         // we will start our row there
        //         if self.row_ptrs[last_inited] == usize::MAX {
        //             row_start = 0;
        //             self.row_ptrs[row_idx] = 0;
        //         } else {
        //             self.row_ptrs[row_idx] = self.row_ptrs[last_inited];
        //             row_start = self.row_ptrs[row_idx];
        //         }
        //     }
        //     assert_ne!(row_start, usize::MAX);
        //     let col_idxs = self.col_idxs.span(row_start..row_end);
        //     match col_idxs.binary_search(&col) {
        //         Ok(at) => self.xs.replace(col_idxs[at], value),
        //         Err(should_be_at) => {
        //             dprintln!(
        //                 "[PE {:>2}] local put: self.cols_idxs.len() = {:?}",
        //                 self.ctx.my_pe(),
        //                 self.col_idxs.len()
        //             );
        //             dprintln!(
        //                 "[PE {:>2}] local put: inserting into self.cols_idxs @ {should_be_at}",
        //                 self.ctx.my_pe()
        //             );
        //             // update col_idxs with the idx we're about to insert
        //             self.col_idxs.insert(should_be_at, col).unwrap();
        //             // offset future row ptrs by one
        //             dprintln!(
        //                 "[PE {:>2}] local put: bumping col_idxs after {should_be_at}",
        //                 self.ctx.my_pe()
        //             );
        //             self.row_ptrs[(row_idx + 1)..]
        //                 .iter_mut()
        //                 .filter(|x| **x != usize::MAX)
        //                 .for_each(|x| *x += 1);
        //             dprintln!(
        //                 "[PE {:>2}] local put: inserting into xs @ {should_be_at}",
        //                 self.ctx.my_pe()
        //             );
        //             self.xs.insert(should_be_at, value).unwrap();
        //         }
        //     }
        //     Ok(())
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
        let (_row_idx, target_pe) = self.global_row_to_pe_row(row).unwrap();
        dprintln!("[PE {:>2}] xs: {:?}", self.ctx.my_pe(), self.xs.span(..));
        dprintln!(
            "[PE {:>2}] row_idxs: {:?}",
            self.ctx.my_pe(),
            &self.row_ptrs[0..=0]
        );
        dprintln!(
            "[PE {:>2}] col_idxs: {:?}",
            self.ctx.my_pe(),
            self.col_idxs.span(..)
        );
        if target_pe == self.mpe {
            dprintln!("[PE {:>2}] local get: {row}, {col}", self.ctx.my_pe());
            let row_start = self.row_ptrs[row];
            let row_end = self.row_ptrs[row + 1];
            if row_start == usize::MAX {
                dprintln!("[PE {:>2}] get bail: row not in array", self.ctx.my_pe());
                return None;
            }
            let col_idxs = self.col_idxs.span(row_start..row_end);
            dprintln!(
                "[PE {:>2}] local get: row_start = {}, col_idxs = {:?}",
                self.ctx.my_pe(),
                row_start,
                col_idxs
            );
            col_idxs
                .binary_search(&col)
                .inspect_err(|at| {
                    dprintln!(
                        "[PE {:>2}] local get bail: search didn't find col, col = {col}, at = {at}",
                        self.ctx.my_pe()
                    )
                })
                .ok()
                .map(|at| self.xs.index_unwrap(at))
        } else {
            dprintln!(
                "[PE {:>2}] remote get: {row}, {col} on PE {:?}",
                self.ctx.my_pe(),
                target_pe
            );
            let (row_start, row_end) = self.ctx.quiet((
                self.row_ptrs.get_single_nbi(row, target_pe, self.ctx),
                self.row_ptrs
                    .get_single_nbi(row + 1, target_pe, self.ctx),
            ));
            if row_start == usize::MAX {
                dprintln!(
                    "[PE {:>2}] remote get bail: row not in array",
                    self.ctx.my_pe()
                );
                return None;
            }
            let col_idxs = self.col_idxs.span_remote(row_start..row_end, target_pe);
            dprintln!(
                "[PE {:>2}] remote get: row_start = {}, col_idxs = {:?}",
                self.ctx.my_pe(),
                row_start,
                col_idxs
            );
            col_idxs
                .binary_search(&col)
                .inspect_err(|_| {
                    dprintln!(
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
        let mut outboxes = (0..self.ctx.n_pes())
            .map(|_| Vec::new())
            .collect::<Vec<_>>();
        for (row, col, x) in xs {
            let (_remote_row_idx, remote_pe) =
                self.global_row_to_pe_row(*row).expect("row out of range");
            outboxes[remote_pe.raw()].push((*row, *col, *x));
        }
        let mut my_incoming = Vec::new();
        dprintln!(
            "[PE {:>2}] outboxes: {outboxes:?}",
            self.ctx.my_pe(),
        );
        for pe in 0..self.ctx.n_pes() {
            let mut outgoing = Shvec::from_iter(self.ctx, self.shm, outboxes[pe].iter().copied());
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

        // step 2: filter out values we don't care about
        // let my_pe = self.ctx.my_pe();
        // let mut xs = xs
        //     .iter()
        //     .map(|(r, c, x)| (self.global_row_to_pe_row(r).unwrap(), c, x))
        //     .filter(|((_row_idx, pe), _c, _x)| *pe == my_pe)
        //     .map(|((row_idx, _), c, x)| (row_idx, c, x))
        //     .collect::<Vec<_>>();
        // xs.sort_by_key(|(r, c, _x)| r * self.cols + c);

        // step 3: allocate space
        let mut buf = self.shm.shbox(self.col_idxs.len() + my_incoming.len());
        buf.reduce_sum(self.ctx);
        self.col_idxs.grow_to(*buf);
        *buf = self.xs.len() + my_incoming.len(); // might be unnecessary
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
        let n = my_incoming.len() as f32;
        dprintln!(
            "[PE {:>2}] incoming: {:?}",
            self.ctx.my_pe(),
            my_incoming
        );
        for (i, (row, col, x)) in my_incoming.into_iter().enumerate() {
            dprintln!(
                "[PE {:>2}] {:.2}% done",
                self.ctx.my_pe(),
                i as f32 / n * 100.0
            );
            dprintln!(
                "[PE {:>2}] putting {x:?} into {row}, {col}",
                self.ctx.my_pe(),
            );
            self.put(row, col, x).unwrap();
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
    matrix.put(mpe, mpe * 2 + 1, mpe).unwrap();
    matrix.put(mpe, mpe * 2, mpe).unwrap();

    println!("row_ptrs = {:?}", &matrix.row_ptrs[..5]);
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
}
