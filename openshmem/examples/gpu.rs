//! Example using OpenSHMEM and CubeCL to render the Mandlebrot
//! set to an image.
//!
//! CubeCL supports CUDA and (through WebGPU) Metal and Vulkan.

use std::error::Error;

use cubecl::prelude::*;

const WIDTH: u32 = 512;
const FWIDTH: f32 = WIDTH as _;
const HEIGHT: u32 = 256;
const FHEIGHT: f32 = HEIGHT as _;
const ARRAY_LEN: u32 = WIDTH * HEIGHT;
const ITERATIONS: u32 = 1000;
const FITERATIONS: f32 = ITERATIONS as _;

#[cube(launch_unchecked)]
fn kernel(output: &mut Array<f32>) {
    if ABSOLUTE_POS < output.len() {
        let pix_x = ABSOLUTE_POS as f32 % FWIDTH;
        let pix_y = ABSOLUTE_POS as f32 * FHEIGHT;
        output[ABSOLUTE_POS] = mandlebrot(pix_x, pix_y);
    }
}

#[cube]
fn mandlebrot(pix_x: f32, pix_y: f32) -> f32 {
    let screen_x = pix_x as f32 / FWIDTH as f32;
    let screen_y = pix_y as f32 / FHEIGHT as f32;
    let scaled_x = screen_x * 2.47 - 2.0;
    let scaled_y = screen_y * 2.24 - 1.12;
    let mut x = 0.0f32;
    let mut y = 0.0f32;

    let mut i = 0;
    loop {
        if i >= ITERATIONS || x * x + y * y > 4.0 {
            break i as f32 / FITERATIONS;
        }
        let next_x = x * x - y * y + scaled_x;
        let next_y = 2.0 * x * y + scaled_y;
        x = next_x;
        y = next_y;
        i += 1;
    };
    i as f32 / FITERATIONS
}

fn launch<R: Runtime>(device: &R::Device) -> Vec<f32> {
    let client = R::client(device);
    let output = client.empty(size_of::<f32>() * ARRAY_LEN as usize);

    // For now, checked launching is unstable.
    //
    // SAFETY: We construct output to be large enough.
    //         We know the client is valid.
    unsafe {
        kernel::launch_unchecked::<R>(
            &client,
            CubeCount::Static(1, 1, 1),
            CubeDim::new(256, 1, 1),
            ArrayArg::from_raw_parts(&output, ARRAY_LEN as usize * size_of::<f32>(), 1),
        )
    };

    let bytes = client.read(output.binding());
    let array = f32::from_bytes(&bytes);
    array.to_vec()
}

fn main() -> Result<(), Box<dyn Error>> {
    let x = launch::<cubecl::wgpu::WgpuRuntime>(&Default::default());
    dbg!(x.len());
    dbg!(x.iter().sum::<f32>() / x.len() as f32);
    dbg!(x.iter().take(256).sum::<f32>() / x.len() as f32);
    dbg!(x.iter().max_by(|a, b| a.total_cmp(b)));
    Ok(())
}
