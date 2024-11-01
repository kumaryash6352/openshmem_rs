use std::{
    error::Error,
    fs::File,
    io::{BufWriter, Write},
    time::Instant,
};

use openshmem_rs::ShmemCtx;

// felt right
const RESOLUTION: (usize, usize) = (8192, 7428);

fn main() -> Result<(), Box<dyn Error>> {
    let ctx = ShmemCtx::init()?;
    let my_pe = ctx.my_pe();
    let is_root = my_pe == 0;
    let npes = ctx.n_pes();
    let max_row_count = RESOLUTION.1 / npes + RESOLUTION.1 % npes;
    let my_row_count = if my_pe == npes - 1 {
        max_row_count
    } else {
        RESOLUTION.1 / npes
    };
    let my_row_start = RESOLUTION.1 / npes * my_pe.raw() as usize;
    let my_row_range = (my_row_start)..(my_row_start + my_row_count);

    let shmallocator = ctx.shmallocator();
    let mut rows = shmallocator.array_default(max_row_count * RESOLUTION.0);

    println!(
        "[PE {my_pe}]: ready to start calculating (row range: {}..{})",
        my_row_range.start, my_row_range.end
    );
    ctx.barrier_all();
    let calc_start = Instant::now();

    for row in my_row_range.clone() {
        for col in 0..RESOLUTION.0 {
            rows[(row - my_row_range.start) * RESOLUTION.0 + col] = pixel(col, row);
        }
    }

    println!(
        "[PE {my_pe}]: finished calculating (row range: {}..{}) ({:.2}px/s)",
        my_row_range.start,
        my_row_range.end,
        (my_row_range.end as f32 - my_row_range.start as f32) * RESOLUTION.0 as f32
            / calc_start.elapsed().as_secs_f32()
    );
    ctx.barrier_all();

    if is_root {
        println!(
            "[PE {my_pe}]: collectively calculated {:.0}px in {:.4}s ({:.2}px/s)",
            RESOLUTION.0 as f32 * RESOLUTION.1 as f32,
            calc_start.elapsed().as_secs_f32(),
            (RESOLUTION.0 as f32 * RESOLUTION.1 as f32) / calc_start.elapsed().as_secs_f32()
        );
        println!("[PE {my_pe}]: saving to output.ppm...");

        let mut out = BufWriter::new(File::create("output.ppm")?);
        writeln!(out, "P3")?;
        writeln!(out, "{} {}", RESOLUTION.0, RESOLUTION.1)?;
        writeln!(out, "255")?;

        for pe in 0..npes {
            println!("[PE {my_pe}]: grabbing data from pe {pe}...");

            let their_element_count = if pe == npes - 1 {
                RESOLUTION.1 / npes + RESOLUTION.1 % npes
            } else {
                RESOLUTION.1 / npes
            } * RESOLUTION.0;

            let their_data = ctx.pe(pe).read(&rows, ..);
            println!(
                "[PE {my_pe}]: got {} elements from pe {pe}, writing...",
                their_data.len()
            );

            for i in 0..their_element_count {
                write!(out, "{x} {x} {x}  ", x = (their_data[i] * 255.0) as usize)?;
            }

            println!("[PE {my_pe}]: wrote data from {pe}");
        }
    } else {
        // Note that the non-root PEs are doing absolutely nothing
        // during this time.
        println!("[PE {my_pe}]: waiting for root to read data...");
    }
    ctx.barrier_all();
    println!("[PE {my_pe}]: done!");

    Ok(())
}

const MAX_ITERATIONS: usize = 100;
fn pixel(x: usize, y: usize) -> f32 {
    // from https://en.wikipedia.org/wiki/Mandelbrot_set#Python_code
    let x0 = x as f32 / RESOLUTION.0 as f32 * 2.47 - 2.;
    let y0 = y as f32 / RESOLUTION.1 as f32 * 2.24 - 1.24;
    let (mut x, mut y) = (0.0f32, 0.0f32);

    for i in 0..MAX_ITERATIONS {
        (x, y) = (x.powi(2) - y.powi(2) + x0, 2.0 * x * y + y0);
        if x.powi(2) + y.powi(2) > 4.0 {
            return i as f32 / MAX_ITERATIONS as f32;
        }
    }
    return 1.0;
}
