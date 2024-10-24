# Physics 427 Homework 7

__Due 11:59pm Wednesday 10/30/2024__

## 1. LU Decomposition of a Tri-diagonal Matrix (15 points)

In this problem, we implement the LU decomposition of a tri-diagonal matrix, in order to prepare for the next homework. I have included a skeleton file `tri_diagonal.h` with a class structure. You will need to implement 3 functions, `compute_lu`, `solve`, and `multiply`. 

The `compute_lu` function should compute the LU decomposition of the given tri-diagonal matrix $A$ (given as three vectors `a`, `b`, and `c`), and populate the values of the two diagonal vectors `l` and `u`. The convention is that all 3 vectors are of size $N$, and $a_0 = c_{n-1} = 0$.

The `solve` function should take in a vector `r` as right hand side of the matrix equation $Ax = r$, and return the solution vector `x`. You should use the LU decomposition computed in the `compute_lu` function to solve the matrix equation.

The `multiply` function is the most straightforward. It takes in a vector `x` and returns the vector $\mathbf{A}\mathbf{x}$.

Note that the class `tri_diagonal` is a template class, and you will need to instantiate it with a type. For example, to instantiate a `tri_diagonal` object with `double` type, you will need to write:
```cpp
tri_diagonal<double> A(a, b, c);
```
This is done so that we can instantiate it with `std::complex<double>` type in the future to solve complex-valued linear systems. Your implementation should not be affected by the fact that this class is a template. Commit your implementation of `tri_diagonal.h` to the Github repository.

I would also like you to implement your own test cases to verify that your implementation is correct. Write a test file called `test_tri_diagonal.cpp` that test all 3 of the function against some known results. Commit this file to the Github repository too. This file needs to compile correctly, and needs to run some non-trivial test cases you define. The program should print whether the test cases passed or failed, similar to the test cases provided in previous homeworks.

## 2. Householder Transformation (15 points)

In this problem, we implement the Householder transformation discussed in class. To remind you what this is, the Householder transformation is an orthogonal matrix, constructed for a given vector $\mathbf{a}$ to set its lower $n - 1$ components to zero.

To facilitate this, I included a very simple matrix library that I wrote myself. The library is contained in `matrix.h`. It simply includes 2 classes: `Vector` and `Matrix`. Both of them are templated similar to what we are using in Problem 1, so you could use them as `Vector<double>` and `Matrix<double>`. For example, you can initialize a 3x3 matrix as following:

``` cpp
Matrix<double> A(3, 3);
A = {{1, 2, 3},
     {4, 5, 6},
     {7, 8, 10}};
```

To access each element of the matrix, you can use `A(i, j)`. The reason you don't use `[]` is because in C++ `[]` is hardcoded to only accept one argument, while `()` doesn't have this restriction. Matrix algebra such as addition, products, multiply by a scalar, multiplying a vector should all work out of the box using the `*` operator, e.g. `C = A * B`. You can print the content of the matrix using `A.print()`. You can take its transpose using `B = A.transpose()`. You can also extract its specific row or column using `A.row(i)` or `A.col(j)`. Both of these functions return a `Vector<T>`. You can get the number of rows or columns using `A.rows()` or `A.cols()`. 

You can also extract a subvector from a `Vector<T>` using `v.subvector(start, end)`, which returns a vector with size `end - start`, and its 0th element will be the same as `v[start]`. This function will be useful in this problem. You can also extract a submatrix from a `Matrix<T>` using `A.submatrix(i, j, nrows, ncols)`. You will need to specify 4 numbers: the starting index `(i, j)`, and the number of rows and columns of the submatrix. To learn more about these two classes, feel free to read the source code. Notice that we did not utilize this class in Problem 1. This is because it's expensive to store a sparse matrix in a dense form. It's much more economical to have a special class that deals with tri-diagonal matrices.

In a header file `problem2.h`, implement a function that constructs a Householder matrix $\mathbf{P} = \mathbf{I} - 2\mathbf{v}\mathbf{v}^T$. You should use the following function signature so that it's easier for us to grade it:

```cpp
template <typename T>
Matrix<T> Householder_matrix(const Vector<T>& a, int last_nonzero = 0);
```

The optional argument `last_nonzero` marks the index of the last element in the given vector `a` that you want to leave nonzero. The Householder matrix will zero out all of the elements after this index. The default is to only keep the 0th element nonzero. When this argument is larger than 0, the first few rows and columns of the Householder matrix should be the identity matrix. You should fill in all the entries of the matrix and return it. 

We will supply our own test cases to test your implementation. To convince yourself that your implementation is correct, you can use the next problem as a test.

## 3. QR Decomposition (10 points)

Based on your implementation of the Householder transformation, implement an algorithm to compute the QR decomposition of a given $n\times n$ square matrix $\mathbf{A}$. The algorithm should construct a series of Householder matrices from each column of the given matrix (you can leave the last column untouched). The orthogonal matrix $\mathbf{Q}$ will be the product of all these Householder matrices, and the upper triangular matrix $\mathbf{R}$ will be the result of all the zeroing.

In a header file `problem3.h`, implement the following function:

```cpp
template <typename T>
void QR_decomposition(const Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R);
```

The matrix `A` is the matrix that we want to decompose, and the arguments `Q` and `R` will store the final results (therefore they are not declared as `const` references).

For a simple test case, the following 3x3 matrix has QR decomposition:

$$
\begin{pmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 10
\end{pmatrix} = 
\begin{pmatrix}
0.123091 & 0.904534 & -0.408248 \\
0.492366 & 0.301511 & 0.816497  \\
0.86164 & -0.301511 & -0.408248
\end{pmatrix}
\begin{pmatrix}
8.12404 & 9.60114 & 11.9399 \\
0 & 0.904534 & 1.50756 \\
0 & 0 & -0.408248 
\end{pmatrix}
$$

Typically QR decompositions are unique upto a diagonal matrix with entries $\pm 1$, so it's okay if your `R` is different from mine by some sign changes. It's also okay if the lower triangular entries of your `R` are not exactly zero, as long as they are on the level of machine precision.

## 4. Diagonalizing a Matrix (10 points)

Now that you have a working QR decomposition algorithm, lets use it to diagonalize a matrix. In a header file `problem4.h`, implement the following function:

```cpp
template <typename T>
Matrix<T> Diagonalize(const Matrix<T>& A, int n_iter);
```

This function should take in a square matrix `A` and return its diagonalized form, carrying out the $\mathbf{R}\mathbf{Q}$ iteration `n_iter` times. The goal is to get the off-diagonal entries as small as possible.

In a separate file, `problem4.cpp`, use this function to diagonalize the following real symmetric matrix:

$$
\mathbf{A} = \begin{pmatrix}
1 & 2 & 3 & 4 & 5 \\
2 & 5 & 6 & 7 & 8 \\
3 & 6 & 3 & 4 & 5 \\
4 & 7 & 4 & 7 & 8 \\
5 & 8 & 5 & 8 & 12
\end{pmatrix}
$$

Your program should simply call `print()` from the diagonalized matrix, which should print out all the eigenvalues (along with all the off-diagonal entries that are hopefully close to zero). You may need to adjust the number of iterations to get an accurate enough result. Feel free to use other tools to diagonalize this matrix, in order to check whether your result makes sense. We expect your eigenvalues are correct to 6 significant digits (the default `cout` precision).