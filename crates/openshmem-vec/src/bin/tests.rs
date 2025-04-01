use std::{
    cell::OnceCell,
    error::Error,
    panic::catch_unwind,
    sync::{Arc, Mutex, OnceLock},
};

use openshmem_rs::{ShmemCtx, PE};

use openshmem_vec::Shvec;

static CTX: OnceLock<ShmemCtx> = OnceLock::new();

fn b(
    f: impl FnOnce() -> Result<(), &'static str> + 'static,
) -> Box<dyn FnOnce() -> Result<(), &'static str>> {
    Box::new(f)
}

pub fn main() {
    CTX.set(ShmemCtx::init().unwrap()).ok();
    let pe = CTX.get().unwrap().my_pe().raw();
    for (name, test) in [
        ("insert", b(test_insert)),
        ("grow", b(test_grow)),
        ("remote_insert", b(test_remote_insert)),
    ] {
        match test() {
            Ok(()) => println!("[PE {pe:>2}] test {name} passed"),
            Err(e) => {
                println!("[PE {pe:>2}] test {name} failed: {e:?}");
            }
        }
    }
}

fn ctx() -> &'static ShmemCtx {
    CTX.get().unwrap()
}

fn test_insert() -> Result<(), &'static str> {
    let shm = CTX.get().unwrap().shmallocator();
    let mut shvec = Shvec::new(ctx(), &shm, 16);
    for i in 0..16 {
        shvec.push(i).map_err(|_| "didn't expect WouldAlloc yet")?;
    }

    Ok(())
}

fn test_grow() -> Result<(), &'static str> {
    let shm = CTX.get().unwrap().shmallocator();
    let mut shvec = Shvec::new(ctx(), &shm, 16);

    for i in 0..16 {
        shvec.push(i).map_err(|_| "didn't expect WouldAlloc yet")?;
    }
    if let None = shvec.push(0).err() {
        return Err("shvec inserted when it should be out of capacity");
    }
    if shvec.grow_to(2) {
        return Err("shvec returned true on grow_to less than current cap");
    }
    shvec.grow_to(20);
    for i in 0..4 {
        shvec.push(i).map_err(|_| "WouldAlloc after growing")?;
    }

    Ok(())
}

fn test_remote_insert() -> Result<(), &'static str> {
    let ctx = CTX.get().unwrap();
    let shm = ctx.shmallocator();
    let mut shvec = Shvec::new(&ctx, &shm, ctx.n_pes());
    if ctx.n_pes() < 2 {
        return Err("not enough PEs");
    }
    for i in 0..ctx.n_pes() {
        shvec
            .push_remote(ctx.my_pe().raw() as u32, PE(i as _))
            .map_err(|_| "shvec should still have capacity")?;
    }
    ctx.barrier_all();
    if shvec.len() != ctx.n_pes() {
        return Err("dropped or extra values in shvec")
    }

    Ok(())
}

fn test_remote_index() -> Result<(), &'static str> {
    let ctx = CTX.get().unwrap();
    let shm = ctx.shmallocator();
    let mut shvec = Shvec::new(&ctx, &shm, ctx.n_pes());


    Ok(())
}
