use openshmem_rs::{shmalloc::Shmallocator, Pod, ShmemCtx, PE};
use openshmem_vec::Shvec;

pub struct CrsMatrix<'ctx, T: Pod + Clone> {
    rows: usize,
    cols: usize,
    ctx: &'ctx ShmemCtx,
    shm: &'ctx Shmallocator<'ctx>,
    // col idxs for all rows, flat
    col_idxs: Shvec<'ctx, usize>,
    xs: Shvec<'ctx, T>,
    // start idx of each row in col_indices
    row_ptrs: Shvec<'ctx, usize>,
}

impl<'ctx, T: Pod + Clone + std::fmt::Debug> CrsMatrix<'ctx, T> {
    pub fn new(rows: usize, cols: usize, ctx: &'ctx ShmemCtx, shm: &'ctx openshmem_rs::shmalloc::Shmallocator<'ctx>) -> Self {
        println!("[PE {:>2}]: creating new CrsMatrix with {} rows, {} cols", ctx.my_pe().raw(), rows, cols);
        let initial_capacity = rows / ctx.n_pes();
        let mut row_ptrs = Shvec::new(ctx, shm, rows + 1);
        
        for _ in 0..=rows {
            row_ptrs.push(0).expect("WouldAlloc shouldn't happen, we allocated enough");
        }

        Self {
            rows,
            cols,
            ctx,
            shm,
            col_idxs: Shvec::new(ctx, shm, initial_capacity),
            xs: Shvec::new(ctx, shm, initial_capacity),
            row_ptrs,
        }
    }

    pub fn nnz(&self) -> usize {
        println!("[PE {:>2}]: calculating nnz", self.ctx.my_pe().raw());
        println!("[PE {:>2}]: values: {:?}", self.ctx.my_pe().raw(), self.xs.span(..));
        
        let mut nnz = self.shm.shbox(self.xs.len());
        nnz.reduce_sum(self.ctx);
        *nnz
    }

    pub fn insert(&mut self, row: usize, col: usize, value: T) {
        println!("[PE {:>2}]: inserting value at row={}, col={}", self.ctx.my_pe().raw(), row, col);
        assert!(row < self.rows && col < self.cols, "Index out of bounds");
        
        let target_pe = row % self.ctx.n_pes();
        let pe = PE(target_pe as u32);
        
        if target_pe == *self.ctx.my_pe() as usize {
            println!("[PE {:>2}]: handling local insert", self.ctx.my_pe().raw());
            self.insert_local(row, col, value);
        } else {
            println!("[PE {:>2}]: remote insert to PE {}", self.ctx.my_pe().raw(), target_pe);
            self.insert_remote(row, col, value, pe);
        }
    }

    pub fn get(&self, row: usize, col: usize) -> Option<T>
    where T: Default {
        println!("[PE {:>2}]: getting value at row={}, col={}", self.ctx.my_pe().raw(), row, col);
        assert!(row < self.rows && col < self.cols, "Index out of bounds");
        
        let target_pe = row % self.ctx.n_pes();
        let pe = PE(target_pe as u32);
        
        if target_pe == *self.ctx.my_pe() as usize {
            println!("[PE {:>2}]: handling local get", self.ctx.my_pe().raw());
            self.get_local(row, col)
        } else {
            println!("[PE {:>2}]: remote get to PE {}", self.ctx.my_pe().raw(), target_pe);
            self.get_remote(row, col, pe)
        }
    }

    fn insert_local(&mut self, row: usize, col: usize, value: T) {
        println!("[PE {:>2}]: insert_local at row={}, col={}", self.ctx.my_pe().raw(), row, col);
        // global row idx to local row idx
        let n_pes = self.ctx.n_pes();
        let local_row = row / n_pes;
        
        let row_start = self.row_ptrs.index_unwrap(local_row);
        let row_end = self.row_ptrs.index_unwrap(local_row + 1);
        
        let mut insert_pos = row_start;
        while insert_pos < row_end {
            let curr_col = self.col_idxs.index_unwrap(insert_pos);
            if curr_col == col {
                println!("[PE {:>2}]: updating existing value at position {}", self.ctx.my_pe().raw(), insert_pos);
                self.xs.replace(insert_pos, value);
                return;
            }
            if curr_col > col {
                break;
            }
            insert_pos += 1;
        }
        
        println!("[PE {:>2}]: inserting new value at position {}", self.ctx.my_pe().raw(), insert_pos);
        // TODO: push_growing
        self.col_idxs.push(col).expect("would alloc");
        self.xs.push(value).expect("would alloc");
        
        // update lcoal row ptrs
        let local_rows = (self.rows + n_pes - 1) / n_pes;
        for i in (local_row + 1)..=local_rows {
            let ptr = self.row_ptrs.index_unwrap(i);
            self.row_ptrs.replace(i, ptr + 1);
        }
    }

    fn insert_remote(&mut self, row: usize, col: usize, value: T, pe: PE) {
        println!("[PE {:>2}]: insert_remote at row={}, col={} to PE {}", self.ctx.my_pe().raw(), row, col, pe.raw());
        let row_start = self.row_ptrs.index_remote(row, pe).unwrap_or(0);
        let row_end = self.row_ptrs.index_remote(row + 1, pe).unwrap_or(0);

        println!("[PE {:>2}]: searching col_idxs[{row_start}..{row_end}]", self.ctx.my_pe());
        let mut insert_pos = row_start;
        while insert_pos < row_end {
            println!("[PE {:>2}]: searching col_idxs[{insert_pos}]", self.ctx.my_pe());
            if let Some(curr_col) = self.col_idxs.index_remote(insert_pos, pe) {
                if curr_col == col {
                    println!("[PE {:>2}]: updating existing remote value at position {}", self.ctx.my_pe().raw(), insert_pos);
                    self.xs.replace_remote(insert_pos, value, pe);
                    return;
                }
                if curr_col > col {
                    break;
                }
            }
            insert_pos += 1;
        }
        
        println!("[PE {:>2}]: inserting new remote value", self.ctx.my_pe().raw());
        self.col_idxs.push_remote(col, pe).expect("would alloc");
        self.xs.push_remote(value, pe).expect("would alloc");
        
        // update row ptrs
        for i in (row + 1)..=self.rows {
            if let Some(ptr) = self.row_ptrs.index_remote(i, pe) {
                self.row_ptrs.replace_remote(i, ptr + 1, pe);
            }
        }
    }

    fn get_local(&self, row: usize, col: usize) -> Option<T>
    where T: Default {
        println!("[PE {:>2}]: get_local at row={}, col={}", self.ctx.my_pe().raw(), row, col);
        // global row idx to local row idx
        let n_pes = self.ctx.n_pes();
        let local_row = row / n_pes;
        
        let row_start = self.row_ptrs.index_unwrap(local_row);
        let row_end = self.row_ptrs.index_unwrap(local_row + 1);
        
        let mut left = row_start;
        let mut right = row_end;
        
        while left < right {
            let mid = left + (right - left) / 2;
            let mid_col = self.col_idxs.index_unwrap(mid);
            
            if mid_col == col {
                println!("[PE {:>2}]: found local value at position {}", self.ctx.my_pe().raw(), mid);
                return Some(self.xs.index_unwrap(mid));
            } else if mid_col < col {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        println!("[PE {:>2}]: local value not found", self.ctx.my_pe().raw());
        None
    }
    // FIXME: the supposed issue in question
    fn get_remote(&self, row: usize, col: usize, pe: PE) -> Option<T>
    where T: Default {
        println!("[PE {:>2}]: get_remote at row={}, col={} from PE {}", self.ctx.my_pe().raw(), row, col, pe.raw());
        if let (Some(row_start), Some(row_end)) = (
            self.row_ptrs.index_remote(row, pe),
            self.row_ptrs.index_remote(row + 1, pe)
        ) {
            // binary search for the col in question
            // TODO: maybe just replace with linear search?
            //       ie self.col_idxs.span(row_start..row_end).iter().find(|rcol| rcol == col)
            let mut left = row_start;
            let mut right = row_end;
            
            while left < right {
                let mid = left + (right - left) / 2;
                if let Some(mid_col) = self.col_idxs.index_remote(mid, pe) {
                    if mid_col == col {
                        println!("[PE {:>2}]: found remote value at position {}", self.ctx.my_pe().raw(), mid);
                        return self.xs.index_remote(mid, pe);
                    } else if mid_col < col {
                        left = mid + 1;
                    } else {
                        right = mid;
                    }
                } else {
                    break;
                }
            }
        } else {
            println!("[PE {:>2}]: row_ptrs[{row} & +1] not found on pe {pe}", self.ctx.my_pe());
        }
        
        println!("[PE {:>2}]: remote value not found", self.ctx.my_pe().raw());
        None
    }
}

pub fn main() {
    let ctx = ShmemCtx::init().unwrap();
    let shm = ctx.shmallocator();
    let rows = 4096;
    let cols = 4096;
    let mut matrix = CrsMatrix::new(rows, cols, &ctx, &shm);


    let mpe = ctx.my_pe().raw();
    matrix.insert(mpe, mpe * 2, mpe);

    ctx.barrier_all();
    assert_eq!(matrix.nnz(), ctx.n_pes());
    for i in 0..ctx.n_pes() {
        assert_eq!(matrix.get(i, i * 2), Some(i), "[PE {:>2}] failed verify at {i}, {}", ctx.my_pe().raw(), i * 2);
    }
}
