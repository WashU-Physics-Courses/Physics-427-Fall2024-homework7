#pragma once

#include <cmath>
#include <vector>
#include <iostream>

template <typename T> class Vector {
public:
  // Constructor, initialize the vector with a given size
  Vector(int size) : n(size) { data.resize(n); }

  // Copy from another vector
  Vector &operator=(const Vector &other) {
    n = other.n;
    data = other.data;
    return *this;
  }

  // Copy from a std::vector
  Vector &operator=(const std::vector<T> &v) {
    n = v.size();
    data = v;
    return *this;
  }

  // Access the i-th element of the vector
  T &operator[](int i) { return data[i]; }

  // Access the i-th element of the vector (const version)
  const T &operator[](int i) const { return data[i]; }

  // Return the size of the vector
  int size() const { return n; }

  // Compute the dot product with another vector
  T dot(const Vector &other) const {
    T sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += data[i] * other[i];
    }
    return sum;
  }

  // Compute the norm of the vector
  T norm() const { return std::sqrt(dot(*this)); }

  // Normalize the vector
  Vector normalize() const { return *this / norm(); }

  // Return a subvector starting at index start and ending at index end
  Vector subvector(int start, int end) const {
    Vector<T> sub(end - start);
    for (int i = start; i < end; ++i) {
      sub[i - start] = data[i];
    }
    return sub;
  }

  Vector operator+(const Vector &other) const {
    Vector<T> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = data[i] + other[i];
    }
    return result;
  }

  Vector &operator+=(const Vector &other) {
    for (int i = 0; i < n; ++i) {
      data[i] += other[i];
    }
    return *this;
  }

  Vector operator-(const Vector &other) const {
    Vector<T> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = data[i] - other[i];
    }
    return result;
  }

  Vector &operator-=(const Vector &other) {
    for (int i = 0; i < n; ++i) {
      data[i] -= other[i];
    }
    return *this;
  }

  Vector operator*(T scalar) const {
    Vector<T> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = data[i] * scalar;
    }
    return result;
  }

  Vector &operator*=(T scalar) {
    for (int i = 0; i < n; ++i) {
      data[i] *= scalar;
    }
    return *this;
  }

  Vector operator/(T scalar) const {
    Vector<T> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = data[i] / scalar;
    }
    return result;
  }

  Vector &operator/=(T scalar) {
    for (int i = 0; i < n; ++i) {
      data[i] /= scalar;
    }
    return *this;
  }

  void print() const {
    for (int i = 0; i < n; ++i) {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }

private:
  int n = 1;
  std::vector<T> data;
};

template <typename T> class Matrix {
public:
  Matrix(int rows, int cols) : n_rows(rows), n_cols(cols) {
    data.resize(n_rows * n_cols);
  }

  Matrix &operator=(const Matrix &other) {
    n_rows = other.n_rows;
    n_cols = other.n_cols;
    data = other.data;
    return *this;
  }

  Matrix &operator=(const std::vector<std::vector<T>> m) {
    n_rows = m.size();
    n_cols = m[0].size();
    data.resize(n_rows * n_cols);
    for (int i = 0; i < n_rows; ++i) {
      for (int j = 0; j < n_cols; ++j) {
        (*this)(i, j) = m[i][j];
      }
    }
    return *this;
  }

  T &operator()(int i, int j) { return data[i * n_cols + j]; }

  const T &operator()(int i, int j) const { return data[i * n_cols + j]; }

  Vector<T> row(int i) const {
    Vector<T> row_data(n_cols);
    for (int j = 0; j < n_cols; ++j) {
      row_data[j] = data[i * n_cols + j];
    }
    return row_data;
  }

  Vector<T> col(int j) const {
    Vector<T> col_data(n_rows);
    for (int i = 0; i < n_rows; ++i) {
      col_data[i] = data[i * n_cols + j];
    }
    return col_data;
  }

  // Return the submatrix starting at index (i, j) with dimensions rows x cols.
  Matrix submatrix(int i, int j, int rows, int cols) const {
    Matrix<T> sub(rows, cols);
    for (int k = 0; k < rows; ++k) {
      for (int l = 0; l < cols; ++l) {
        sub(k, l) = (*this)(i + k, j + l);
      }
    }
    return sub;
  }

  Matrix transpose() const {
    Matrix<T> transposed(n_cols, n_rows);
    for (int i = 0; i < n_rows; ++i) {
      for (int j = 0; j < n_cols; ++j) {
        transposed(j, i) = (*this)(i, j);
      }
    }
    return transposed;
  }

  Vector<T> operator*(const Vector<T> &v) const {
    Vector<T> result(n_rows);
    for (int i = 0; i < n_rows; ++i) {
      result[i] = row(i).dot(v);
    }
    return result;
  }

  Matrix operator*(const Matrix &other) const {
    Matrix<T> result(n_rows, other.n_cols);
    for (int i = 0; i < n_rows; ++i) {
      for (int j = 0; j < other.n_cols; ++j) {
        T sum = 0;
        for (int k = 0; k < n_cols; ++k) {
          sum += (*this)(i, k) * other(k, j);
        }
        result(i, j) = sum;
      }
    }
    return result;
  }

  Matrix &operator*=(const Matrix &other) {
    *this = *this * other;
    return *this;
  }

  Matrix operator*(T scalar) const {
    Matrix<T> result(n_rows, n_cols);
    for (int i = 0; i < n_rows; ++i) {
      for (int j = 0; j < n_cols; ++j) {
        result(i, j) = (*this)(i, j) * scalar;
      }
    }
    return result;
  }

  Matrix &operator*=(T scalar) {
    for (int i = 0; i < n_rows; ++i) {
      for (int j = 0; j < n_cols; ++j) {
        (*this)(i, j) *= scalar;
      }
    }
    return *this;
  }

  int rows() const { return n_rows; }
  int cols() const { return n_cols; }

  static Matrix<T> identity(int n) {
    Matrix<T> I(n, n);
    for (int i = 0; i < n; ++i) {
      I(i, i) = 1.0;
    }
    return I;
  }

  void print() {
    for (int i = 0; i < n_rows; ++i) {
      for (int j = 0; j < n_cols; ++j) {
        std::cout << (*this)(i, j) << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  int n_rows = 1;
  int n_cols = 1;
  std::vector<T> data;
};
