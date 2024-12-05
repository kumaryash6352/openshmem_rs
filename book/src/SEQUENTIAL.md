# Naive Implementation

We'll first implement a naive solution, directly mirroring what we'd do
by hand.

## The Matrix Itself

First, we need a type to represent our matrix:

```rs
struct Matrix {
    data: Vec<f32>,
    dim: (usize, usize)
}
```

For the sake of simplicity, we'll use a row-major representation. The `dim` field
represents the amount of rows and columns respectively in the matrix.

> In real world code, you probably want to reach for one of the 
> well made linear algebra libraries such as [faer](https://github.com/sarah-quinones/faer-rs) 
> or [nalgebra](https://github.com/dimforge/nalgebra). And by probably, we mean
> I'll hunt you down with a bent spoon if you roll your
> own matrix when premade solutions are more than sufficient.

Then, we need two ways to index the matrix: by row and by column.

## Indexing the Matrix

Indexes by row are trivial: take a slice of the matrix data from the start of the
given row to the start of the next row.
```rs
fn row(matrix: &Matrix, n: usize) -> &[f32] {
    matrix.data[(matrix.dim.1 * n)..(matrix.dim.1 * (n + 1))]
}
```

> These examples panic on invalid accesses. We'll be handling these better later.

Indexes by column are a little more tricky. We can use an `Iterator` with the `step_by`
modifier to iterate over elements in a column, avoiding extra memory allocations.

```rs
fn col(matrix: &Matrix, n: usize) -> impl Iterator<Item = &f32> {
    assert!(n < matrix.dim.0);
    matrix.data.iter().skip(n).step_by(matrix.dim.1)
}
```

We'll change `row` to match.

```rs
//                               new |------------------------|
fn row(matrix: &Matrix, n: usize) -> impl Iterator<Item = &f32> {
    //                                                   new |-----|
    matrix.data[(matrix.dim.1 * n)..(matrix.dim.1 * (n + 1))].iter()
}
```

We'll then give this a little test.

```rs
#[test]
fn test_idx() {
    let m = Matrix {
        data: vec![1.0, 2.0, 3.0, 4.0],
        dim: (2, 2)
    };
    assert_eq!(row(&m, 0).copied().collect::<Vec<_>>(), &[1.0, 2.0]);
    assert_eq!(col(&m, 0).copied().collect::<Vec<_>>(), &[1.0, 3.0]);
}
```

```bash
$ cargo test
   Compiling sequential v0.1.0 (/../sequential)
    Finished `test` profile [unoptimized + debuginfo] target(s) in 0.27s
     Running unittests src/main.rs (target/debug/deps/sequential-640cf2f340b7ea03)
running 1 test

test test_idx ... ok

test result: ok. 1 passed; 0 failed; 0 ignored; 0 measured; 0 filtered outtest test_idx ... ok
```

Since the test passed, we know that the `row` and `col` functions are doing
what we want them to.

## Dot Products

Now, we implement a dot product. Since we're using iterators, this is trivial: we take
the elements of one vector, pair them up with the elements in the other vector,
multiply and sum.

```rs
fn dot(xs: impl Iterator<Item = f32>, ys: impl Iterator<Item = f32>) -> f32 {
    xs.zip(ys).map(|(x, y)| x * y).sum()
}
```

And because we're good little programmers, we'll write a test.

```rs
#[test]
fn test_dot_product() {
    let x = vec![1.0, 2.0, 3.0];
    let y = vec![3.0, 6.0, 9.0];
    // x dot y = 42
    assert!((42.0 - dot(x.into_iter(), y.into_iter())).abs() < 0.00001);
}
```

Since we're dealing with floating point multiplies, we can start
running into small inaccuracies, so we allow a bit of leniency in the result.

## Calculating Elements

Now that we have a dot product function, we'll make a function to find each
element in the product of two matrices.

```rs
fn mult_element(x: usize, y: usize, a: &Matrix, b: &Matrix) -> f32 {
    dot(row(a, x).copied(), col(b, y).copied())
}
```

And a test.

```rs
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
```

## Putting It All Together

Now we have all of the pieces of the puzzle we need for a full matrix multiplication.

```rs
fn matrix_mult(a: &Matrix, b: &Matrix) -> Matrix {
    let mut prod = Matrix {
        data: vec![0.0; a.dim.0 * b.dim.1],
        dim: (a.dim.0, b.dim.1)
    };

    for row in 0..a.dim.0 {
        for col in 0..b.dim.1 {
            prod.data[row * a.dim.0 + col] = mult_element(row, col, a, b);
        }
    }

    prod
}
```

Oh, and a test.

```rs
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
```
