#pragma once

#include <cstddef>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include "coordinate.cpp"
#include "iterator.cpp"

// The storage class represents a "square matrix" of
// arbitrary objects (the template argument T)
// Each element in the square matrix
// corresponds to a point2d. So the element in the ith-row
// and j-th column is associated to the point2d{i, j}
// We need to be able to resize the matrix, access/modify its elements
// and check for a given point whether or not it is within the matrix.
// Attention the following code is incomplete. You are not allowed
// to change the given signature but you can add member functions and variables
// to the class as you see fit

template <class T> class storage {
public:
  storage() = delete;

  // n is expected to be the total number of elements,
  // not the number of rows/cols
  // If n != (std::sqrt(n))*(std::sqrt(n))
  // a runtime_error has to be thrown
  explicit storage(size_t n) {
    square = std::sqrt(n);
    if (n != square * square) {
      throw std::runtime_error("Wrong number (" + std::to_string(n) +
                               "): number of elements must be a square number");
    }
    matrix.resize(n);
  }

  // todo
  storage(const storage &other) = default;
  storage &operator=(const storage &other) = default;

  /*
  storage &operator=(const storage &s) {
    auto length = s.matrix.size();
    for (size_t i = 0; i < length; ++i) {
      matrix.push_back(s.matrix[i]);
    }
    square = s.square;
  }
  */

  // Accessing a point outside of the
  // storage has to throw an exception
  // Use operator() to acces elements
  // We need a const and a non-const version
  // todo

  coord max_coord() const { return square; }

  // Check if a given point exists within this representation
  bool has_point(const point2d &p) const {
    return p.x < square && p.y < square;
  }

  // todo
  // This function should RESERVE (like the function for std::vector)
  // at least n elements (and verify that it is still a square matrix)
  void reserve(unsigned n) { matrix.reserve(square * square + n); }

  // This function should RESIZE (like the function for std::vector)
  // the storage to hold at least n elements
  // (and verify that it is still a square matrix)
  void resize(unsigned n) {
    unsigned new_square = std::sqrt(n);

    if (n != new_square * new_square) {
      throw std::runtime_error("Wrong number (" + std::to_string(n) +
                               "): number of elements must be a square number");
    }

    matrix.resize(n);
  }

  T &get_point(size_t x, size_t y) {
    if (has_point(point2d(x, y))) {
      return matrix[x + y * square];
    }
    throw std::runtime_error("Point not in matrix");
  }

  void set_point(size_t x, size_t y, T point) {
    if (has_point(point2d(x, y))) {
      matrix[x + y * square] = point;
    }
    throw std::runtime_error("Point not in matrix");
  }

  T &operator()(point2d point) {
    if (has_point(point)) {
      return get_point(point.x, point.y);
    }
  }

  // Convenience accessor
  T *get_storage() { return matrix; };

protected:
  std::vector<T> matrix;
  size_t square;
};
