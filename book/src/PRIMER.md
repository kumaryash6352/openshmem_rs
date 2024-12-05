# Primer: Matrix Multiplication

If your linear algebra is a bit rusty, here's a quick overview of matrix multiplication.

Unlike a vector dot product which produces a scalar, a matrix multiplication produces
another matrix.

If we have two matrices, \\(A\\) and \\(B\\), and the number of columns \\(\text{cols}(A) = n\\) is the same as the number of
rows in \\(B\\), then the element at the \\(i\\)th row and \\(j\\)th column of the product \\(AB\\) is defined as:

\\[ (AB)\_{ij} = \sum\_{k = 1}^{n} A\_{ik}B\_{kj} \\]

Another way to think about the formula for each element is that the element is
the dot product of the \\(i\\)th row of A and the \\(j\\)th column of B.

This produces a matrix with \\(rows(A)\\) rows and \\(cols(B)\\) columns. 

Matrix multiplications are at the heart of many computational models:
- Matrices with a determinant—sort of like an n-dimensional volume—of 1 are rotations when multiplied, which are used in computer graphics.
- Matrices are multiplied with their transposition in least-squares approximations.
- Matrices are multiplied with an input vector during a forward propagation in machine learning.

As such, they often come up when attempting to simulate or model a situation. A faster matrix multiplication can have far
reaching impact.
