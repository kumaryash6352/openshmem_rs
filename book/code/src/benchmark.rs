use std::time::Instant;

pub trait Benchmarkable {
    type State;

    fn init() -> Result<Self::State, Box<dyn std::error::Error>>;
    fn set_matrices(
        state: &mut Self::State,
        new_dim_a: (usize, usize), new_data_a: Vec<f32>,
        new_dim_b: (usize, usize), new_data_b: Vec<f32>
    );
    fn execute(state: &mut Self::State);
}

const SEED: u32 = 0xDABBAD00;

fn rand(state: &mut u32) -> f32 {
    const A: u32 = 1103515245;
    const C: u32 = 12345;
    let res = state.wrapping_mul(A).wrapping_add(C);
    *state = res;
    let normalized = res as f32 / u32::MAX as f32;
    // number between -5.0 and 5.0
    normalized * 10.0 - 5.0
}

fn flops(n: usize, m: usize, p: usize, time: f32) -> f32 {
    // from https://math.stackexchange.com/a/484662
    let ops = n * p * (2 * m - 1);
    ops as f32 / time
}

pub fn bench<Impl: Benchmarkable>() -> Result<(), Box<dyn std::error::Error>> {
    let mut state = Impl::init()?;
    let mut rng = SEED;
    let mut times = Vec::new();

    // a is a n x m matrix
    // b is a m x p matrix
    for (n, m, p) in [
        (32, 32, 32),
        (1, 32, 1),
        (32, 1, 32),
        (256, 256, 256),
        (512, 512, 512),
        (512, 256, 512),
        (256, 512, 256),
        (2048, 2048, 2048)
    ] {
        let gen_start = Instant::now();
        println!("generating matrices: a={n}x{m}, b={m}x{n}");
        let mut a = vec![0.0; n * m];
        let mut b = vec![0.0; m * p];
        a.iter_mut().for_each(|e| *e = rand(&mut rng));
        b.iter_mut().for_each(|e| *e = rand(&mut rng));
        println!("generated {} elements in {:.02}ms",
                 (n + p) * m, gen_start.elapsed().as_secs_f32() / 1000.0
        );
        Impl::set_matrices(&mut state, (n, m), a, (m, p), b);
        println!("executing multiply");
        let mult_start = Instant::now();
        Impl::execute(&mut state);
        let time_taken = mult_start.elapsed().as_secs_f32();
        println!("multiplied {} elements in {:.06}s", (n + p) * m, time_taken);
        times.push(((n, m, p), time_taken));
    }

    println!("breakdown:");
    println!("n\tm\tp\tsecs\tflops");
    for ((n, m, p), time) in times {
        println!("{n}\t{m}\t{p}\t{:.05}\t{:.00}", time, flops(n, m, p, time));
    }
    Ok(())
}
