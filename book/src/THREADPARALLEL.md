# Parallel across Threads: Rayon

If you're coming from the C programming space, you may have heard of OpenMP.

OpenMP defines a set of pragmas, or compiler annotations, that are used to parallelize
common control flows such as for-loops. For example, if you wanted to double the elements of an array `a` in parallel:

```c
#pragma omp parallel for simd
for(int i = 0; i < n; i++)
    a[i] = a[i] * 2;
```

[Rayon](https://github.com/rayon-rs/rayon) is the equivalent[^rayonvsopenmp] for Rust.
While it's made more for consumer applications, it'll do just fine for many HPC applications.

While OpenMP relies on compiler support and directives, Rayon is implemented in Rust, within Rust.
Rayon defines the `ParallelIterator` trait, along with several others, which have `par_*` counterparts
to many of the methods from the `Iterator` trait.

For example, say you had the following code which doubled elements of a slice.

```rs
a.iter_mut().for_each(|e| *e *= 2.0);
```

A parallel version with Rayon wouldn't be all that different.

```rs
a.par_iter_mut().for_each(|e| *e *= 2.0);
```

For many cases, all you need to do to parallelize a workload using Rayon is to translate
the workload into an `Iterator` method chain, then replace `iter[_mut]` with `par_iter[_mut]`.

We have one of those cases! We'll have our matrix multiplication generate the elements
in parallel, but we don't need to change the rest of the code.

First, we need to add Rayon as a dependancy.

```
$ cargo add rayon
    Updating crates.io index
      Adding rayon v1.10.0 to dependencies
             Features:
             - web_spin_lock
```

Then, we change how we iterate over the array.

Instead of `for`-loops, we'll use a range iterator over the entire
range of indexes into our result, then we'll calculate what row and column we're on.


```rs
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
```

Then we test.

```
$ cargo test
[..]
test result: ok. 8 passed; 0 failed; 0 ignored; 0 measured; 0 filtered out; finished in 0.00s
```

OK, everything's looking good. Let's hook it into our harness see the numbers!

```rs
pub struct ThreadParallel;

impl Benchmarkable for ThreadParallel {
      // ... same code as Sequential
```
```diff
// main.rs:
fn main() -> Result<(), Box<dyn std::error::Error>> {
-    benchmark::bench::<Sequential>()?;
+    benchmark::bench::<ThreadParallel>()?;
```

```
$ cargo run
[..]
breakdown:
n       m       p       secs    flops
32      32      32      0.00039 166751536
1       32      1       0.00001 6841876
32      1       32      0.00019 5335640
256     256     256     0.00340 9847746560
512     512     512     0.02243 11955944448
512     256     512     0.01018 13163712512
256     512     256     0.00437 15324771328
```

The machine this was run on had 11 cores, and we saw a ~5x speedup on the `n = p = 256, m = 512` case.

It's not linear scaling, but it's certainly something.

[^rayonvsopenmp]: Rayon doesn't support some of the more interesting features of
                  OpenMP, like accelerator offloading or schedule selection. However, like OpenMP,
                  it does make parallelizing code significantly easier.
