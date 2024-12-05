# Parallelizing our Workload

If we want to speed up our workload, we'll need to find some way
to split it up across threads.

A fairly easy way to parallelize this workload is to split the resultant
matrix up into two parts.

If we're multiplying \\(A_{n\times m}\\) by \\(B_{m\times p}\\),
we'll get a matrix \\((AB)_{n\times p}\\).

We'll split that matrix into rows; if we have \\(X\\) threads, we'll have
each thread handle \\(n / X\\) rows[^whycols], except for the last thread which
gets the remainder slapped onto its workload.

Then, once we've parallelized it across threads, we'll distribute the work
over nodes using a similar paradigm.

[^whycols]: If you're going for maximum throughput with our row-major matrices,
            you'd probably want split it up by columns instead. That means each
            thread only has to index the matrix by-column once, then can use that
            data for all \\(n\\) elements in the result's column. We won't do that,
            because we didn't do that in our sequential implementation.

