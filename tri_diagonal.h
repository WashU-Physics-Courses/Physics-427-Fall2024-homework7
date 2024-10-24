#pragma once

#include <cmath>
#include <iostream>
#include <vector>

// This class represents a tridiagonal matrix of size n x n. We use
// a template so that we can use this class with different types of
// data (int, float, double, etc.)
template <typename T>
class tri_diagonal {
public:
  tri_diagonal(const std::vector<T>& a0, const std::vector<T>& b0,
               const std::vector<T>& c0) {
    // a, b, c are the diagonals of the matrix. all of them are of size n
    a = a0;
    b = b0;
    c = c0;
    u.resize(a.size());
    l.resize(a.size());
    // y is a temporary vector used in solve
    y.resize(a.size());
  }

  void compute_lu() {
    // TODO: Implement this
  }

  std::vector<T> solve(const std::vector<T> &r) {
    if (r.size() != a.size()) {
      std::cout << "Error: r.size() != a.size()" << std::endl;
      return std::vector<T>();
    }
    std::vector<T> x(r.size());

    // TODO: Implement the rest of the function. You may want to use the
    // temporary vector y

    return x;
  }

  std::vector<T> multiply(const std::vector<T> &x) {
    if (x.size() != a.size()) {
      std::cout << "Error: x.size() != a.size()" << std::endl;
      return std::vector<T>();
    }
    std::vector<T> result(x.size());

    // TODO: Implement the rest of the function

    return result;
  }

  std::vector<T> a, b, c;
  std::vector<T> l, u;
  std::vector<T> y; // temporary vector used in solve
};
