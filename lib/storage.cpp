#include <cstddef>
#include <iostream>
#include <math.h>
#include <string>

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
    try {
      if (n != square * square) {
        throw "Wrong number (" + std::to_string(n) +
            "): number of elements must be a square number";
      }
      matrix = (T *)malloc(n * sizeof(T));
    } catch (std::string err) {
      std::cout << "Init: " + err << std::endl;
    }
  }

  // todo
  storage(const storage &other) {
    square = other.square;
    matrix = other.matrix;
  };

  storage &operator=(const storage &s) {
    size_t length = sizeof(s.matrix[0]) / sizeof(*s.matrix);
    matrix = malloc(length);
    for (size_t i = 0; i < length; ++i) {
      matrix[i] = s.matrix[i];
    }
    square = s.square;
  }

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
  void reserve(unsigned n) { resize(square * square + n); }

  // This function should RESIZE (like the function for std::vector)
  // the storage to hold at least n elements
  // (and verify that it is still a square matrix)
  void resize(unsigned n) {
    unsigned new_square = std::sqrt(n);
    try {
      if (n != new_square * new_square)
        throw "Wrong number (" + std::to_string(n) +
            "): number of elements must be a square number";
    } catch (std::string e) {
      std::cout << "Resize: " + e;
    }

    T *new_matrix = (T *)malloc(n * sizeof(T));

    for (size_t i = 0; i < new_square; i++) {
      for (size_t j = 0; j < new_square; j++) {
        if (i < square && j < square)
          new_matrix[i + j * new_square] = matrix[i + j * square];
      }
    }

    square = new_square;
    matrix = new_matrix;
  }

  T &get_point(size_t x, size_t y) {
    try {
      if (has_point(point2d(x, y))) {
        return matrix[x + y * square];
      }
      throw "Point not in matrix";
    } catch (std::string e) {
      std::cout << e;
    }
  }

  void set_point(size_t x, size_t y, T point) {
    try {
      if (has_point(point2d(x, y))) {
        matrix[x + y * square] = point;
      }
      throw "Point not in matrix";
    } catch (std::string e) {
      std::cout << e;
    }
  }

  T &operator()(point2d point) {
    if (has_point(point)) {
      return get_point(point.x, point.y);
    }
  }

  // Convenience accessor
  T *get_storage() { return matrix; };

protected:
  T *matrix;
  size_t square;
};
