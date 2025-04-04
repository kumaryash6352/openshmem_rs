use std::{
    ffi::c_void,
    mem::{self, swap, transmute, MaybeUninit},
    ops::{Index, RangeBounds},
};

use openshmem_rs::{
    atomics::Atomic, ffi::{shmem_collectmem, SHMEM_TEAM_WORLD}, shmalloc::{Shbox, Shmallocator}, shmutex::{Shmlock, ShmlockLock}, AnyBitPattern, Pod, ShmemCtx, PE, Zeroable
};

/// Analogous to `Vec`, but on the Symmetric Heap.
///
/// # Why AnyBitPattern?
///
/// MaybeUninit is not Pod, even if T is Pod.
/// See this issue for more details: https://github.com/Lokathor/bytemuck/pull/160
pub struct Shvec<'ctx, T: Zeroable + Copy> {
    shm: &'ctx Shmallocator<'ctx>,
    ctx: &'ctx ShmemCtx,
    len: Shbox<'ctx, Atomic<usize>>,
    lck: Shbox<'ctx, [Shmlock<'ctx>]>,
    buf: Shbox<'ctx, [MaybeUninit<T>]>,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct WouldRealloc;

impl<'ctx, T: Zeroable + Copy> Shvec<'ctx, T> {
    pub fn new(
        ctx: &'ctx ShmemCtx,
        shm: &'ctx Shmallocator<'ctx>,
        initial_capacity: usize,
    ) -> Self {
        Self {
            ctx,
            shm,
            len: shm.shbox(Atomic::new(0)),
            lck: shm.array_gen(|_| shm.lock(), ctx.n_pes()),
            buf: shm.array_gen(|_| MaybeUninit::uninit(), initial_capacity),
        }
    }

    pub fn from_iter<I>(ctx: &'ctx ShmemCtx, shm: &'ctx Shmallocator<'ctx>, iter: I) -> Self
    where
        I: IntoIterator<Item = T>,
    {
        let buf = iter.into_iter().collect::<Vec<_>>();
        let mut items = shm.shbox(buf.len());
        items.reduce_max(ctx);
        let buf = (0..*items)
            .map(|i| {
                buf.get(i)
                    .cloned()
                    .map(MaybeUninit::new)
                    .unwrap_or(MaybeUninit::zeroed())
            })
            .collect::<Vec<_>>();

        Self {
            ctx,
            shm,
            buf: shm.array_gen(|i| buf[i], buf.len()),
            lck: shm.array_gen(|_| shm.lock(), ctx.n_pes()),
            len: shm.shbox(Atomic::new(*items)),
        }
    }

    pub fn index(&self, idx: usize) -> Option<T> {
        if self.len.atomic_fetch_local(self.ctx) <= idx {
            None
        } else {
            Some(unsafe { self.buf[idx].assume_init() })
        }
    }

    pub fn index_many(&self, idxs: &[usize]) -> Box<[T]> {
        let len = self.len.atomic_fetch_local(self.ctx);
        let mut buf = Box::new_uninit_slice(idxs.len());
        for i in 0..idxs.len() {
            if i >= len {
                panic!("index in index_many out of bounds");
            }
            buf[i] = self.buf[idxs[i]];
        }
        unsafe { buf.assume_init() }
    }

    pub fn index_many_remote(&self, idxs: &[usize], pe: PE) -> Box<[T]> {
        let len = self.len.atomic_fetch(pe, self.ctx);
        assert!(
            idxs.iter().all(|idx| *idx < len),
            "index in index_many_remote out of bounds"
        );
        unsafe {
            self.ctx
                .quiet(
                    idxs.iter()
                        .map(|idx| self.buf.get_single_nbi(*idx, pe, self.ctx))
                        .collect::<Vec<_>>(),
                )
                .into_boxed_slice()
                .assume_init()
        }
    }

    pub fn span(&self, range: impl RangeBounds<usize>) -> &[T] {
        let len = self.len.atomic_fetch_local(self.ctx);
        let end = match range.end_bound() {
            std::ops::Bound::Included(x) => *x + 1,
            std::ops::Bound::Excluded(x) => *x,
            std::ops::Bound::Unbounded => len,
        };
        let start = match range.start_bound() {
            std::ops::Bound::Included(x) => *x,
            std::ops::Bound::Excluded(x) => *x + 1,
            std::ops::Bound::Unbounded => 0,
        };
        let end = end.min(self.len());

        // SAFETY: we know start..end is initialized because len > end or we'd have panic'd
        unsafe { transmute(&self.buf[start..end]) }
    }

    pub fn span_remote(&self, range: impl RangeBounds<usize>, pe: PE) -> Box<[T]> {
        let len = self.len.atomic_fetch(pe, self.ctx);
        let end = match range.end_bound() {
            std::ops::Bound::Included(x) => *x + 1,
            std::ops::Bound::Excluded(x) => *x,
            std::ops::Bound::Unbounded => len,
        };
        let start = match range.start_bound() {
            std::ops::Bound::Included(x) => *x,
            std::ops::Bound::Excluded(x) => *x + 1,
            std::ops::Bound::Unbounded => 0,
        };
        let end = end.min(len);

        // SAFETY: we know start..end is initialized because len > end or we'd have panic'd
        unsafe { self.buf.get_many(pe, start..end, self.ctx).assume_init() }
    }

    pub fn replace(&mut self, idx: usize, x: T) {
        assert!(
            self.len.atomic_fetch_local(self.ctx) > idx,
            "tried to replace out of bounds"
        );
        self.buf[idx] = MaybeUninit::new(x);
    }

    pub fn replace_remote(&mut self, idx: usize, x: T, pe: PE) {
        assert!(
            self.len.atomic_fetch(pe, self.ctx) > idx,
            "tried to replace out of bounds"
        );
        self.buf.put_single(idx, &MaybeUninit::new(x), pe, self.ctx);
    }

    pub fn replace_remote_many(&mut self, data: &[(usize, T)], pe: PE) {
        let len = self.len.atomic_fetch(pe, self.ctx);
        assert!(
            data.iter().all(|(idx, _)| *idx < len),
            "index in replace_many_remote out of bounds"
        );
        // TODO: gots to be a better way
        data.iter()
            .cloned()
            .map(|(idx, x)| (idx, MaybeUninit::new(x)))
            .for_each(|(idx, mx)| mem::forget(self.buf.put_single_nbi(idx, &mx, pe, self.ctx)));
        self.ctx.quiet(());
    }

    pub fn index_unwrap(&self, idx: usize) -> T {
        assert!(
            self.len.atomic_fetch_local(self.ctx) > idx,
            "index {idx} out of bounds"
        );
        unsafe { self.buf[idx].assume_init() }
    }

    pub fn index_remote(&self, idx: usize, pe: PE) -> Option<T> {
        let remote_len = self.len.atomic_fetch(pe, self.ctx);
        if remote_len <= idx {
            return None;
        }

        let res = self.buf.get_single(pe, idx, self.ctx);
        Some(unsafe { res.assume_init() })
    }

    pub fn grow_to(&mut self, new_capacity: usize) -> bool {
        if new_capacity > self.buf.len() {
            // SAFETY: we take a mutable reference to self, so no
            //         other threads are holding on to the lock.
            unsafe { self.lck[*self.ctx.my_pe() as usize].lock_raw() };
            let mut new_buf = self.shm.array_gen(|_| MaybeUninit::uninit(), new_capacity);
            // SAFETY: we know self.buf has at least self.len initialized elements
            //         by the safety requirements of self.len.
            //         we also know self.buf and new_buf do not overlap since we just allocated
            //         new_buf
            unsafe {
                std::ptr::copy_nonoverlapping(
                    self.buf.as_ptr(),
                    new_buf.as_mut_ptr(),
                    self.len.atomic_fetch_local(&self.ctx),
                );
            }
            self.buf = new_buf;
            unsafe { self.lck[*self.ctx.my_pe() as usize].unlock_raw() };
            true
        } else {
            false
        }
    }

    pub unsafe fn grow_to_no_lock(&mut self, new_capacity: usize) -> bool {
        if new_capacity > self.buf.len() {
            let mut new_buf = self.shm.array_gen(|_| MaybeUninit::uninit(), new_capacity);
            unsafe {
                std::ptr::copy_nonoverlapping(
                    self.buf.as_ptr(),
                    new_buf.as_mut_ptr(),
                    self.len.atomic_fetch_local(&self.ctx),
                );
            }
            self.buf = new_buf;
            true
        } else {
            false
        }
    }

    pub fn push(&mut self, value: T) -> Result<usize, WouldRealloc> {
        self.push_remote(value, self.ctx.my_pe())
    }

    pub fn push_remote(&mut self, value: T, pe: PE) -> Result<usize, WouldRealloc> {
        let upe = pe.raw();
        let _guard = self.lck[upe].lock();
        let remote = self.ctx.pe(upe);
        let remote_len = self.len.atomic_fetch(pe, self.ctx);
        if remote_len >= self.buf.len() {
            Err(WouldRealloc)
        } else {
            remote.put_single(&mut self.buf, remote_len, &MaybeUninit::new(value));
            self.len.atomic_inc(pe, self.ctx);
            self.ctx.quiet(());
            Ok(remote_len)
        }
    }

    pub fn push_growing(&mut self, value: T) -> usize {
        //let guard = self.lck.lock_raw()
        todo!()
    }

    pub fn len(&self) -> usize {
        self.len.atomic_fetch_local(self.ctx)
    }

    pub fn iter<'s>(&'s self) -> ShvecIter<'s, T> {
        ShvecIter {
            len: self.len(),
            idx: 0,
            buf: self,
            _lock: self.lck[self.ctx.my_pe().raw() as usize].lock(),
        }
    }

    pub fn insert(&mut self, idx: usize, x: T) -> Result<(), WouldRealloc> {
        // SAFETY: we borrow self mutably, so no other thread can have this lock
        unsafe {
            self.lck[self.ctx.my_pe().raw() as usize].lock_raw();
        }
        let len = self.len.atomic_fetch_local(self.ctx);
        if idx > len {
            panic!("idx out of bounds for insert");
        }
        // if we have 0 unused slots left
        if self.buf.len() < len + 1 {
            return Err(WouldRealloc);
        }
        let src = idx..(self.buf.len() - 1);
        self.buf.copy_within(src, idx + 1);
        self.buf[idx] = MaybeUninit::new(x);
        self.len.atomic_inc(self.ctx.my_pe(), self.ctx);

        Ok(())
    }

    pub fn collect(&self) -> Box<[T]> {
        let mut len = self.shm.shbox(self.len());
        len.reduce_sum(self.ctx);
        let mut buf: Box<[MaybeUninit<T>]> = Box::new_uninit_slice(*len);

        unsafe {
            shmem_collectmem(
                SHMEM_TEAM_WORLD,
                buf.as_mut_ptr() as *mut c_void,
                self.buf.raw_ptr() as *const c_void,
                size_of::<T>() * self.len(),
            )
        };
        unsafe { buf.assume_init() }
    }

    pub fn shift(&mut self, fill_with: T, starting_from: usize, amt: isize) -> Result<(), WouldRealloc> {
        if amt.is_positive() {
            self.shift_right(fill_with, starting_from, amt as _)
        } else {
            todo!("left shift not yet implemented");
        }
    }

    pub fn shift_right(&mut self, fill_with: T, starting_from: usize, amt: usize) -> Result<(), WouldRealloc> {
        let len = self.len();
        assert!(starting_from < len, "shift_right starting from out of bounds");
        if len + amt >= self.buf.len() {
            return Err(WouldRealloc);
        }

        let guard = self.lck[self.ctx.my_pe().raw()].lock();
        // move all values after starting_from to the right
        self.buf.copy_within(starting_from.., starting_from + amt);
        // fill previous values with fill_with
        self.buf[starting_from..(starting_from + amt)].fill(MaybeUninit::new(fill_with));
        // adjust len
        self.len.atomic_add(amt, self.ctx.my_pe(), self.ctx);
        drop(guard);

        Ok(())
    }
}

pub struct ShvecIter<'vec, T: Zeroable + Copy> {
    len: usize,
    idx: usize,
    buf: &'vec Shvec<'vec, T>,
    _lock: ShmlockLock<'vec, 'vec>,
}

impl<'vec, T: Zeroable + Copy> Iterator for ShvecIter<'vec, T> {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        if self.idx < self.len {
            let t = self.buf.index(self.idx);
            self.idx += 1;
            t
        } else {
            None
        }
    }
}

// impl<'ctx, T: Pod> Index<usize> for Shvec<'ctx, T> {
//     type Output = T;

//     fn index(&self, idx: usize) -> &Self::Output {
//         assert!(idx < self.len.atomic_fetch_local(self.ctx), "local index out of bounds");
//         unsafe {
//             self.buf[idx].assume_init_ref()
//         }
//     }
// }
