use rayon::prelude::*;

#[derive(Debug)]
pub struct Matrix {
    data: Vec<f32>,
    dim: (usize, usize)
}

fn col(matrix: &Matrix, n: usize) -> impl Iterator<Item = &f32> {
    assert!(n < matrix.dim.1);
    matrix.data.iter().skip(n).step_by(matrix.dim.1)
}

fn row(matrix: &Matrix, n: usize) -> impl Iterator<Item = &f32> {
    matrix.data[(matrix.dim.1 * n)..(matrix.dim.1 * (n + 1))].iter()
}

#[test]
fn test_idx() {
    let m = Matrix {
        data: vec![1.0, 2.0, 3.0, 4.0],
        dim: (2, 2)
    };
    assert_eq!(row(&m, 0).copied().collect::<Vec<_>>(), &[1.0, 2.0]);
    assert_eq!(col(&m, 0).copied().collect::<Vec<_>>(), &[1.0, 3.0]);
}

fn dot(xs: impl Iterator<Item = f32>, ys: impl Iterator<Item = f32>) -> f32 {
    xs.zip(ys).map(|(x, y)| x * y).sum()
}

#[test]
fn test_dot_product() {
    let x = vec![1.0, 2.0, 3.0];
    let y = vec![3.0, 6.0, 9.0];
    // x dot y = 42
    assert!((42.0 - dot(x.into_iter(), y.into_iter())).abs() < 0.00001);
}

fn mult_element(x: usize, y: usize, a: &Matrix, b: &Matrix) -> f32 {
    dot(row(a, x).copied(), col(b, y).copied())
}

#[test]
fn test_matrix_mult_element() {
    let a = Matrix {
        data: vec![1.0, 2.0, 3.0, 4.0, 5.0, 6.0],
        dim: (2, 3)
    };
    let b = Matrix {
        data: vec![1.5, 2.5, 3.5],
        dim: (3, 1)
    };
    // (xy)[0, 0] = 1.0 * 1.5 + 2.0 * 2.5 + 3.0 * 3.5 = 17
    assert!((mult_element(0, 0, &a, &b) - 17.0).abs() < 0.00001);
}

fn matrix_mult(a: &Matrix, b: &Matrix) -> Matrix {
    let data = (0..(a.dim.0 * b.dim.1)).into_par_iter().map(|idx| {
            mult_element(idx / b.dim.1, idx % b.dim.1, a, b)
    });

    let prod = Matrix {
        data: data.collect(),
        dim: (a.dim.0, b.dim.1)
    };

    prod
}

#[test]
fn test_matrix_mult() {
    let a = Matrix {
        data: vec![1.0, 2.0, 3.0, 4.0, 5.0, 6.0],
        dim: (2, 3)
    };
    let b = Matrix {
        data: vec![1.5, 2.5, 3.5],
        dim: (3, 1)
    };
    let c = matrix_mult(&a, &b);
    let (exp_x, exp_y) = (17.0, 39.5);
    let (x, y) = (c.data[0], c.data[1]);
    assert!((x - exp_x).abs() < 0.00001);
    assert!((y - exp_y).abs() < 0.00001);
}

pub struct ThreadParallel;

impl crate::benchmark::Benchmarkable for ThreadParallel {
    type State = (Matrix, Matrix);

    fn init() -> Result<Self::State, Box<dyn std::error::Error>> {
        Ok((Matrix {
            data: vec![],
            dim: (0, 0)
        }, Matrix {
            data: vec![],
            dim: (0, 0)
        }))
    }

    fn set_matrices(
        state: &mut Self::State,
        dim_a: (usize, usize),
        data_a: Vec<f32>,
        dim_b: (usize, usize),
        data_b: Vec<f32>
    ) {
        state.0 = Matrix {
            data: data_a,
            dim: dim_a
        };
        state.1 = Matrix {
            data: data_b,
            dim: dim_b
        };
    }

    fn execute(state: &mut Self::State) {
        let _ = std::hint::black_box(matrix_mult(&state.0, &state.1));
    }
}
