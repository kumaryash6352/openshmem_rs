# Benchmarking our Implementation

We'll need a way to figure out if we're actually getting faster or not.

We'll be optimizing for strictly matrix multiplication; we don't care how
long it takes to initialize the matrix. 

## Benchmarkables

What we'll do is make a trait that
our benchmarking harness could use to interact with the different implementations
we make.

```rs
trait Benchmarkable {
    type State;

    fn init() -> Result<Self::State, Box<dyn std::error::Error>>;
    fn set_matrices(
        state: &mut Self::State,
        new_dim_a: (usize, usize), new_data_a: Vec<f32>,
        new_dim_b: (usize, usize), new_data_b: Vec<f32>
    );
    fn execute(state: &mut Self::State);
}
```

> Once again, please use actual solutions like [criterion.rs](https://github.com/bheisler/criterion.rs)
> or cargo's built-in benchmarking tools in real code. We implement our own
> benchmark harness for the sake of example.

This trait gives us a common interface to interact with the solutions
we'll make down the line. The trait is eliminated at compile-time, in
a process known as "monomorphization"—where the Rust compiler eliminates
generics by creating a version of the function for each type it's called
with.

Our harness is pretty simple: for a type that implements `Benchmarkable`, we call `init`,
unwrap the state, then for various matrix sizes:
1. Call `set_matrix` with a pair of random matrices.
2. Track the time a call to `execute` takes.

## Generating our Data

Since we're gonna need random values for our matrices,
we need an RNG.

> Please use [rand](https://github.com/rust-random/rand) or
> similar in real code. Bent spoon and all that.

For the sake of simplicity, we'll use a [linear congruential generator](https://en.wikipedia.org/wiki/Linear_congruential_generator).
These use the last generated number, multiply by some constant \\(A\\), and add some constant \\(C\\)
to construct a random number. We'll use the constants from glibc, which produce ~31 bits of random.

```rs
fn rand(state: &mut u32) -> f32 {
    const A: u32 = 1103515245;
    const C: u32 = 12345;
    let res = state.wrapping_mul(A).wrapping_add(C);
    *state = res;
    let normalized = res as f32 / u32::MAX as f32;
    // number between -5.0 and 5.0
    normalized * 10.0 - 5.0
}
```

> You'll notice we use methods instead of just multiplying or adding
> to the state. In Rust, arithmetic panics on wrap or overflow by default.
> We can use these wrapping methods to say that overflow and wrapping
> are desired behavior.

We want consistant data between benchmarks, so we'll use a constant seed value.

```rs
const SEED: u32 = 0xDABBAD00;
```

It'd also be useful to see how many FLOPs we get, given two matrix dimensions
and a time taken to multiply. We'll be using the same general algorithm for our parallel
solution, so we can define a single function for both.

```rs
fn flops(n: usize, m: usize, p: usize, time: f32) -> f32 {
    // from https://math.stackexchange.com/a/484662
    let ops = n * p * (2 * m - 1);
    ops as f32 / time
}
```

## Benchmark Loop

Then, we implement our loop.

```rs
fn bench<Impl: Benchmarkable>() -> Result<(), Box<dyn std::error::Error>> {
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
        (256, 512, 256)
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
}
```

## Writing our Benchmark Adapter

Now, all we need to do in order to benchmark our sequential
solution is to implement `Benchmarkable` on a type. We'll
use a zero-sized type for this.

```rs
struct Sequential;

impl Benchmarkable for Sequential {
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
```

You'll notice the `black_box` function in the body of `execute`.
`black_box` tells the compiler to treat the value it's passed as used, even
if it isn't. Without the call to `black_box`, the Rust compiler would
be free to say, "hey, they don't end up using this value for anything
that's observable to the outside world, let me just optimize that out."

Now we just need to edit our `main` to run the benchmark.

```rs
fn main() -> Result<(), Box<dyn std::error::Error>> {
    bench::<Sequential>()
}
```

## Running our Benchmark

Well, we have our benchmark harness and we have our implementation, so let's
get some numbers!

```
$ cargo run
...
generating matrices: a=32x1, b=1x32
generated 64 elements in 0.00ms
executing multiply
thread 'main' panicked at src/sequential.rs:9:5:
assertion failed: n < matrix.dim.0
note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
```

Uh oh.

## Debugging our Rust Program

> If you're already experienced with debugging programs in Rust,
> you may wish to skip to the [next section](#back-to-benchmarking-results).

Things are going wrong. We *could* just slap a few `dbg!`'s around, but
we're good little programmers, so we'll use a debugger.

> This example uses LLDB because GDB support for ARM64 Mac's isn't there.
> The process we follow should apply to most debuggers.

Now, here's a fun fact about Rust: panics are graceful. What I mean is that:
- Panicking is considered a valid end to a program.
- Panicking calls destructors for variables in scope.
- **Panicking isn't picked up automatically by debuggers.**

As such, for the sake of convenience, we'll turn panics not-so graceful
so our debugger picks them up.

In our `Cargo.toml`, we'll add the following:
```toml
[profile.dev]
panic = "abort"
```

```
$ cargo build
...
thread 'main' panicked at src/sequential.rs:9:5:
assertion failed: n < matrix.dim.0
note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
zsh: abort      ./target/debug/book-example
```

We've caused the program to abort. Success!

Now, we hit our program with a debugger.

```
$ lldb ./target/debug/book-example
Current executable set to '/../target/debug/book-example'
(lldb) r
Process 96981 launched: '/../target/debug/book-example'
..
thread 'main' panicked at src/sequential.rs:9:5:
assertion failed: n < matrix.dim.0
note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
Process 96981 stopped
* thread #1, name = 'main', queue = 'com.apple.main-thread', stop reason = signal SIGABRT
    frame #0: 0x0000000183d095f0 libsystem_kernel.dylib`__pthread_kill + 8
libsystem_kernel.dylib`:
->  0x183d095f0 <+8>:  b.lo   0x183d09610               ; <+40>
    0x183d095f4 <+12>: pacibsp 
    0x183d095f8 <+16>: stp    x29, x30, [sp, #-0x10]!
    0x183d095fc <+20>: mov    x29, sp
Target 0: (book-example) stopped.
```

Looking at where we are, we seem to have stopped outside of our program.
Somewhere in the kernel, which we don't really care about. Let's check
the backtrace.

```
(lldb) bt
* thread #1, name = 'main', queue = 'com.apple.main-thread', stop reason = signal SIGABRT
  * frame #0: 0x0000000183d095f0 libsystem_kernel.dylib`__pthread_kill + 8
    frame #1: 0x0000000183d41c20 libsystem_pthread.dylib`pthread_kill + 288
    frame #3: 0x000000010002e1d4 book-example`panic_abort::__rust_start_panic::abort::hb7136a1fe6d6bcb8 at lib.rs:48:17 [opt]
    frame #4: 0x000000010002e1c8 book-example`__rust_start_panic at lib.rs:43:5 [opt]
    frame #5: 0x0000000100025ae4 book-example`rust_panic at panicking.rs:862:25 [opt]
    frame #6: 0x00000001000259b0 book-example`std::panicking::rust_panic_with_hook::h7570b4f0d25a01d8 at panicking.rs:826:5 [opt]
    frame #7: 0x00000001000255b4 book-example`std::panicking::begin_panic_handler::_$u7b$$u7b$closure$u7d$$u7d$::he5841e7b0bac65ee at panicking.rs:667:13 [opt]
    [.. snip ~20 lines ..]
    frame #26: 0x00000001000207d8 book-example`std::rt::lang_start_internal::hc66084bf1c82dd9f [inlined] std::panicking::try::do_call::h80c352325820505e at panicking.rs:557:40 [opt]
    frame #27: 0x00000001000207d8 book-example`std::rt::lang_start_internal::hc66084bf1c82dd9f [inlined] std::panicking::try::h5e54ed5e7302a90f at panicking.rs:520:19 [opt]
    frame #28: 0x00000001000207d8 book-example`std::rt::lang_start_internal::hc66084bf1c82dd9f [inlined] std::panic::catch_unwind::h1ae1a88d9ae3a908 at panic.rs:358:14 [opt]
    frame #29: 0x00000001000207d8 book-example`std::rt::lang_start_internal::hc66084bf1c82dd9f at rt.rs:174:20 [opt]
    frame #30: 0x0000000100007220 book-example`std::rt::lang_start::h3461759a8b1829bc(main=(book-example`book_example::main::h602296d79d77fb29 at main.rs:6), argc=1, argv=0x000000016fdff
    frame #31: 0x0000000100007340 book-example`main + 36
    frame #32: 0x00000001839b7154 dyld`start + 2476
```

Oh boy.

> What follows may be skipped if you're not interested.

You'll notice that the vast majority of the backtrace is taken up by Rust's runtime, indicated
by the `std::rt` module. You may have also been told that Rust doesn't have a runtime.

Rust has a runtime, which does initialization work before the program's `main` function
is executed. This runtime handles things like saving `argv`, setting up a panic hook,
and initializing the stack. Some people claim that Rust doesn't have a runtime because
compared to something like Python or Go, the Rust runtime is very, very small. However,
the runtime is there, and we've hit one of the few cases where it's annoying to work with.

> Skip here if you weren't interested.

The important parts of this backtrace are what includes our code: anything in the `book_example` module.

```
[..]
    frame #11: 0x0000000100040694 book-example`core::panicking::panic::h71633a2ea1952dec at panicking.rs:148:5 [opt]
+---frame #12: 0x0000000100002d70 book-example`book_example::sequential::col::ha3e4ab6bce5986a2(matrix=0x000000016fdfd890, n=1) at sequential.rs:9:5
|   frame #13: 0x0000000100002ed4 book-example`book_example::sequential::mult_element::hbc8a130bf2accef7(x=0, y=1, a=0x000000016fdfd868, b=0x000000016fdfd890) at sequential.rs:40:29
|   frame #14: 0x0000000100003050 book-example`book_example::sequential::matrix_mult::h8ad61e278ea49ab3(a=0x000000016fdfd868, b=0x000000016fdfd890) at sequential.rs:65:46
|   frame #15: 0x000000010000326c book-example`_$LT$book_example..sequential..Sequential$u20$as$u20$book_example..benchmark..Benchmarkable$GT$::execute::h10f908ca09e6cb5b(state=0x000000016fdfd868) at sequential.rs:122:38
|   frame #16: 0x0000000100006eb0 book-example`book_example::benchmark::bench::h7cee618c19353066 at benchmark.rs:61:9
+---frame #17: 0x00000001000072b8 book-example`book_example::main::h602296d79d77fb29 at main.rs:7:5
    frame #18: 0x0000000100004588 book-example`core::ops::function::FnOnce::call_once::h772984a6972a1f85((null)=(book-example`book_example::main::h602296d79d77fb29 at main.rs:6), (null)=<unavailable>) at function.rs:250:5
[..]
```

You'll see that we called the `col` function with `n = 1`. This means we asked for the second column (our matrices are zero-indexed)
of some matrix at `0x000000016fdfd890`. Let's see if we can get more info.

```
(lldb) x 0x000000016fdfd890
0x16fdfd890: 20 00 00 00 00 00 00 00 80 c2 53 00 00 60 00 00   .........S..`..
0x16fdfd8a0: 20 00 00 00 00 00 00 00 01 00 00 00 00 00 00 00   ...............
```

Oh.

> Remember what I said about LLDB being close enough to other debuggers?
> If you're following along in GDB, you probably got something very different
> out of that command—something very readable. GDB has fantastic support for
> Rust programs. LLDB doesn't.

We can improve the situation by using `rust-lldb`, which usually comes with your Rust install.


```
$ rust-lldb ./target/debug/book-example
..
(lldb) bt
..
    frame #9: 0x0000000100025294 book-example`rust_begin_unwind at panicking.rs:665:5 [opt]
    frame #10: 0x0000000100040624 book-example`core::panicking::panic_fmt::h31c1fa88ce29f60b at panicking.rs:76:14 [opt]
    frame #11: 0x0000000100040694 book-example`core::panicking::panic::h71633a2ea1952dec at panicking.rs:148:5 [opt]
    frame #12: 0x0000000100002d70 book-example`book_example::sequential::col::ha3e4ab6bce5986a2(matrix=0x000000016fdfd860, n=1) at sequential.rs:9:5
    frame #13: 0x0000000100002ed4 book-example`book_example::sequential::mult_element::hbc8a130bf2accef7(x=0, y=1, a=0x000000016fdfd838, b=0x000000016fdfd860) at sequential.rs:40:29
    frame #14: 0x0000000100003050 book-example`book_example::sequential::matrix_mult::h8ad61e278ea49ab3(a=0x000000016fdfd838, b=0x000000016fdfd860) at sequential.rs:65:46
..
(lldb) frame select 14
frame #14: 0x0000000100003050 book-example`book_example::sequential::matrix_mult::h8ad61e278ea49ab3(a=0x000000016fdfd838, b=0x000000016fdfd860) at sequential.rs:65:46
   62  
   63       for row in 0..a.dim.0 {
   64           for col in 0..b.dim.1 {
-> 65               prod.data[row * b.dim.1 + col] = mult_element(row, col, a, b);
   66           }
   67       }
   68  
(lldb) p *a
(book_example::sequential::Matrix) {
  data = size=32 {
    [0] = 2.36001921
    ..
    [31] = 4.76307869
  }
  dim = {
    0 = 32
    1 = 1
  }
}
```

Alright, we get much more info upfront now. Let's think about this for a second:
1. The call to `col` fails.
2. We call `col` with `matrix = b` and `n = 1`.
3. The assertion in `col` preemptively fails so we don't just get
   an empty vector back.

Well, does it make sense to ask for the `n`th column of `b`?
```
(lldb) p b->dim
((usize, usize)) {
  0 = 1
  1 = 32
}
```
Our `b` has 32 columns, which means the code asking for the second column
is completely valid. Therefore, the issue must be in our assertion. Let's
take another look at it.
```
(lldb) bt
..
    frame #11: 0x0000000100040694 book-example`core::panicking::panic::h71633a2ea1952dec at panicking.rs:148:5 [opt]
    frame #12: 0x0000000100002d70 book-example`book_example::sequential::col::ha3e4ab6bce5986a2(matrix=0x000000016fdfd860, n=1) at sequential.rs:9:5
    frame #13: 0x0000000100002ed4 book-example`book_example::sequential::mult_element::hbc8a130bf2accef7(x=0, y=1, a=0x000000016fdfd838, b=0x000000016fdfd860) at sequential.rs:40:29
..
(lldb) frame select 12
   6    }
   7   
   8    fn col(matrix: &Matrix, n: usize) -> impl Iterator<Item = &f32> {
-> 9        assert!(n < matrix.dim.0);
   10       matrix.data.iter().skip(n).step_by(matrix.dim.1)
   11   }
   12  
```

So we assert that the column we request is less than the amount of rows in the matrix...

Well, there's our issue. We check the wrong number!

```diff
fn col(matrix: &Matrix, n: usize) -> impl Iterator<Item = &f32> {
-    assert!(n < matrix.dim.0);
+    assert!(n < matrix.dim.1);
    matrix.data.iter().skip(n).step_by(matrix.dim.1)
}
```

```
$ cargo run
breakdown:
n   m   p           secs        flops
..
```

🎉 Success!

## Back to Benchmarking: Results

```
$ cargo run
..
breakdown:
n       m       p       secs    flops
32      32      32      0.00600 10757004
1       32      1       0.00001 4973554
32      1       32      0.00065 1569450
256     256     256     0.47600 70355208
512     512     512     3.54592 75628712
512     256     512     1.79184 74758496
256     512     256     0.88579 75687816
```

Looks like we suffer a performance penalty
whenever one of our matrices are super close to 
columnar; this part is probably due to choosing a
row-major layout for the matrix.

But wait a minute; we're measuring in the 70 megaflop range!
That seems really low for a modern machine, which should be able
to at least get a few hundred megaflops per core on such a compute-focused workload.

This is not acceptable performance.

## Optimizing our Program

The first thing to check when optimizing a Rust program
is what options you're giving the compiler. Specifically:
is your code in debug mode?

Our code is in debug mode, since we've just been running `cargo run`.

We can do a release build using `cargo run --release`, but since we
still want debug info, we'll instead say that debug builds should
have all optimizations turned on. We can do this by adding the following
to our `Cargo.toml`:

```diff
[profile.dev]
-panic = "abort" # from debugging
+opt-level = 3
```

Now when we run `cargo run`, Cargo will build an executable with debug info
and assertions, but will also optimize the result. 

Now let's try again.

```
$ cargo run
    Finished `dev` profile [optimized + debuginfo] target(s) in 0.00s
     Running `target/debug/book-example`
..
breakdown:
n       m       p       secs    flops
32      32      32      0.00006 1026035840
1       32      1       0.00000 189189184
32      1       32      0.00001 112219176
256     256     256     0.02708 1236568320
512     512     512     0.10286 2607257856
512     256     512     0.04471 2996380928
256     512     256     0.02213 3029898752
```

There we go!

### Profiling

We'll start with a flamegraph to see where we're actually spending time.
We'll use the `cargo-flamegraph` tool to do so.

```
$ cargo install flamegraph
```

If you run it right now, you'll get a warning about needing to enable
debug info in release builds-sort of the reverse of what we did earlier.
We can do so temporarily by setting an environment variable.

```
$ CARGO_PROFILE_RELEASE_DEBUG=true cargo flamegraph
..
breakdown:
n       m       p       secs    flops
32      32      32      0.00003 2554930688
1       32      1       0.00000 36863664
32      1       32      0.00000 546133376
256     256     256     0.01353 2474312704
512     512     512     0.10257 2614472448
512     256     512     0.05120 2616364800
256     512     256     0.02587 2591163392
dtrace: pid 1173 has exited
writing flamegraph to "flamegraph.svg"

$ open flamegraph.svg
```

> On some devices, this command may require root privileges.

TODO: remaining

### Footnote: Domain Optimization

In theory, if we wanted very fast row and column slicing, we could store
two copies of the data buffer for the matrix: one that's row-major, and
one that's column-major. That way, when we want to index by row or by column,
we're always taking a contiguous slice of some data buffer.

This has been left out ~due to time constraints~ as an exercise to the reader.
