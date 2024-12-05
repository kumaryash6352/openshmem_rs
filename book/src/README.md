# Introduction

This is a step-by-step guide, showcasing the process of taking a Rust
program and fully parallelizing it using the `openshmem-rs` OpenSHMEM wrapper
and the Rust ecosystem of packages, such as [Rayon](https://github.com/rayon-rs/rayon). 

The guide is written with the following audiences in mind:
- HPC programmers experienced with C, wanting to experiment with Rust.
- Programmers experienced with Rust, who want to try highly parallel programming.

Depending on which camp you fall into, if any, there may be sections of the guide that 
feel redundant to you. Feel free to skip these.

We'll use matrix multiplication as our example workload. We'll go from a naive, sequential 
implementation to a node-parallel, SIMD accelerated solution.

The complete code is available in the [code/](../../code) directory.
