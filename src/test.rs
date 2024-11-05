/// Note that all tests assume Sandia OpenSHMEM version 1.5.
///
/// There are not currently plans to support other versions in these tests.



use std::{convert::identity, error::Error, sync::OnceLock};

use ctor::ctor;

use super::*;

static CTX: OnceLock<ShmemCtx> = OnceLock::new();

#[ctor]
fn init() {
    CTX.set(ShmemCtx::init().unwrap()).ok();
}

#[test]
fn ctx_meta() -> Result<(), Box<dyn Error>> {
    let ctx = CTX.get().unwrap();
    ctx.barrier_all();

    let my_pe = ctx.my_pe().raw();
    let npes = ctx.n_pes();
    assert_ne!(my_pe, usize::MAX);
    assert!(my_pe < npes);
    assert_eq!(ctx.info_get_name_str(), "Sandia OpenSHMEM");

    Ok(())
}

#[test]
fn shbox() -> Result<(), Box<dyn Error>> {
    let ctx = CTX.get().unwrap();
    ctx.barrier_all();
    let shmalloc = ctx.shmallocator();
    let my_pe = ctx.my_pe().raw();

    let mut x = shmalloc.shbox(my_pe);

    dbg!(x.raw_ptr());
    assert!(x.raw_ptr().is_aligned());
    assert!(!x.raw_ptr().is_null());
    assert!(*x == my_pe);
    *x = my_pe + 1;
    assert!(*x == my_pe + 1);

    Ok(())
}

#[test]
fn sharray() -> Result<(), Box<dyn Error>> {
    let ctx = CTX.get().unwrap();
    ctx.barrier_all();
    let shmalloc = ctx.shmallocator();
    let my_pe = ctx.my_pe().raw();

    let mut x = shmalloc.array_gen(identity, 8);

    assert!(!x.raw_ptr().is_null());
    assert!((x.raw_ptr() as *const usize).is_aligned());
    assert_eq!(x.iter().sum::<usize>(), (0..8).sum());
    let mut view = ctx.pe(my_pe).write(&mut x, ..);
    view[0] = view[7];
    view.finish();
    assert_eq!(x.iter().sum::<usize>(), (0..8).sum::<usize>() + 6);

    Ok(())
}
