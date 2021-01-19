#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <vector>

using coord = int;

// Defnes the diference between two points. Note that you should define the
// basic operations of addition and substraction between points and offsets.
struct offset2d {
  offset2d() = delete;
  offset2d(coord dx_in, coord dy_in) : dx(dx_in), dy(dy_in){};

  offset2d(const offset2d &o) = default;
  offset2d &operator=(const offset2d &o) = default;

  // Basic operations.
  bool operator==(const offset2d &o) const {
    return (dx == o.dx && dy == o.dy);
  }
  bool operator!=(const offset2d &o) const {
    return (dx != o.dx || dy != o.dy);
  }
  bool operator<(const offset2d &o) const { return (dx < o.dx && dy < o.dy); }

  offset2d &operator+=(const offset2d &o) {
    dx += o.dx;
    dy += o.dy;
    return *this;
  }

  offset2d &operator-=(const offset2d &o) {
    dx -= o.dx;
    dy -= o.dy;
    return *this;
  }

  offset2d operator+(const offset2d &other) const {
    return offset2d({dx + other.dx, dy + other.dy});
  }
  offset2d operator-(const offset2d &other) const {
    return offset2d({dx - other.dx, dy - other.dy});
  }

  unsigned norm() const { return std::max(abs(this->dx), abs(this->dy)); }
  coord dx, dy;
};

// Defines a point in the grid, mainly a pair of coordinates.
struct point2d {
  point2d() = delete;
  point2d(coord x_in, coord y_in) : x(x_in), y(y_in){};

  point2d(const point2d &o) = default;
  point2d &operator=(const point2d &o) = default;

  // Basic operations.
  bool operator==(const point2d &o) const { return (x == o.x && y == o.y); }
  bool operator!=(const point2d &o) const { return (x != o.x || y != o.y); }
  bool operator<(const point2d &o) const { return (x < o.x && y < o.y); }
  point2d &operator+=(const offset2d &o) {
    x += o.dx;
    y += o.dy;
    return *this;
  }

  point2d &operator-=(const offset2d &o) {
    x -= o.dx;
    y -= o.dy;
    return *this;
  }

  coord x, y;
};

point2d operator+(const point2d &p, const offset2d &o) {
  return point2d({p.x + o.dx, p.y + o.dy});
}
point2d operator+(const offset2d &o, const point2d &p) {
  return point2d({p.x + o.dx, p.y + o.dy});
}
point2d operator-(const point2d &p, const offset2d &o) {
  return point2d({p.x - o.dx, p.y - o.dy});
}
point2d operator-(const offset2d &o, const point2d &p) {
  return point2d({o.dx - p.x, o.dy - p.y});
}
offset2d operator-(const point2d &p1, const point2d &p2) {
  return offset2d({p1.x - p2.x, p1.y - p2.y});
}

enum class field_state {
  NONE = 0,
  FREE,
  ENTRANCE,
  EXIT,
  DAMAGING,
  DEADLY,
  BLOCKED,
};

enum field_type {
  PATH = ' ',
  ENTRANCE = 'I',
  LARGE_TRAP = 'T',
  SMALL_TRAP = 't',
  HIDDEN_TRAP = 'H',
  WALL = 'w',
  EXIT = 'O',
  FOG = 'X',
  PLAYER = 'P',
};

// To properly describe the effects,
// we need to keep track of the (accumulated) damage
// AND the state
// Why is it sufficient to have one member variable of type field_state?
struct field_effect {
  field_effect &operator+=(const field_effect &other) {
    this->damage += other.damage;
    if (other.state > this->state)
      this->state = other.state;
    return *this;
  }

  field_effect(field_state s) : state(s), damage(0) {}

  field_effect(field_state s, unsigned d) : state(s), damage(d) {}

  bool operator==(const field_effect &other) {
    return this->state == other.state && this->damage == other.damage;
  }

  bool operator!=(const field_effect &o) { return !(*this == o); }

  field_state state = field_state::NONE;
  unsigned damage = 0;
};
// utils.h stop

// fields.h start
// Base class for all fields
// A field needs to be representable by a char
// (to print the game on the console)
// and we have to be able to evaluate its effects
// a field can effect the cell where it is located, but also surrounding cells.
// To avoid storing a fields own location, we will use the relative distance
// to the cell for which we want to evaluate effect
class field {
public:
  field(char c) : c_{c} {}

  virtual ~field() {}

  char to_char() const { return c_; }

  void set(char c) const { c_ = c; }

  // o corresponds to the distance of this field to the one for which we want
  // to evaluate
  // The boolean argument is_sim has the following role:
  // when evaluating the field for a turn of the actual game is_sim = false
  // if the AI-player evaluates the field -> is_sim is true
  // this way we can implement hidden traps that are not triggered by the AI
  virtual field_effect effect(const offset2d &o, bool is_sim = true) const = 0;

  // Helper function -> arg <-> zero offset
  field_effect effect() const { return effect({0, 0}); }

private:
  mutable char c_;
};

// Note that the constructors for the derived classes do
// not take any argument
class maze_entrance : public field {
public:
  maze_entrance() : field(field_type::ENTRANCE) {}
  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0))
      return field_effect(field_state::ENTRANCE);
    return field_effect(field_state::NONE);
  }
};

class maze_exit : public field {
public:
  maze_exit() : field(field_type::EXIT) {}
  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0))
      return field_effect(field_state::EXIT);
    return field_effect(field_state::NONE);
  }
};

class wall : public field {
public:
  wall() : field(field_type::WALL) {}
  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0))
      return field_effect(field_state::BLOCKED);
    return field_effect(field_state::NONE);
  }
};

class path : public field {
public:
  path() : field(field_type::PATH) {}
  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0))
      return field_effect(field_state::FREE);
    return field_effect(field_state::NONE);
  }
};

class small_trap : public field {
public:
  small_trap() : field(field_type::SMALL_TRAP) {}
  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0))
      return field_effect(field_state::DEADLY);
    return field_effect(field_state::NONE);
  }
};

class large_trap : public field {
public:
  large_trap() : field(field_type::LARGE_TRAP) {}
  field_effect effect(const offset2d &o, bool is_sim = true) const {
    if (o.norm() <= 1)
      return field_effect(field_state::DAMAGING, 5);
    return field_effect(field_state::NONE);
  }
};

class hidden_trap : public field {
  bool damaged = false;

public:
  hidden_trap() : field(field_type::HIDDEN_TRAP) {
    this->set(field_type::PATH);
  }

  field_effect effect(const offset2d &o, bool is_sim = true) const {
    if (o.norm() <= 1) {
      this->set(field_type::LARGE_TRAP);
      return field_effect(field_state::DAMAGING, 5);
    }
    return field_effect(field_state::NONE);
  }
};

using field_ptr = std::shared_ptr<field>;

// A function which converts a char to a shared pointer to a field
// This function will be useful to generate a maze from a string
field_ptr to_field(char c) {
  switch (c) {
  case field_type::WALL:
    return std::make_unique<wall>(wall());
  case field_type::ENTRANCE:
    return std::make_unique<maze_entrance>(maze_entrance());
  case field_type::EXIT:
    return std::make_unique<maze_exit>(maze_exit());
  case field_type::SMALL_TRAP:
    return std::make_unique<small_trap>(small_trap());
  case field_type::LARGE_TRAP:
    return std::make_unique<large_trap>(large_trap());
  case field_type::HIDDEN_TRAP:
    return std::make_unique<hidden_trap>(hidden_trap());
  default:
    return std::make_unique<path>(path());
  }
}
// fields.h stop

class box_iterator {
public:
  // The following is not strictly necessary for our code
  // however if you want to have an iterator confirming to the
  // c++ standard you need this.
  using iterator_category = std::forward_iterator_tag;
  using value_type = point2d;
  // Has no sense for forward iterators but must be specified for
  // certain platforms in order to compile (g++ for instance)
  using difference_type = void;
  using pointer = point2d *;
  using reference = point2d &;

  box_iterator(coord x_beg, coord x_end, coord y_beg, coord y_end)
      : x_beg_(x_beg), x_end_(x_end), y_beg_(y_beg), y_end_(y_end),
        c_pos_(point2d({x_beg, y_beg})){};

  box_iterator(coord x_beg, coord x_end, coord y_beg, coord y_end,
               point2d char_pos)
      : x_beg_(x_beg), x_end_(x_end), y_beg_(y_beg), y_end_(y_end),
        c_pos_(char_pos){};

  box_iterator(const point2d &lower_left, const point2d &upper_right)
      : x_beg_(lower_left.x), x_end_(upper_right.x), y_beg_(lower_left.y),
        y_end_(upper_right.y), c_pos_(point2d({lower_left.x, lower_left.y})){};
  // Create the box from the lower_left corner (belongs to the box)
  // and the upper_right corner (just outside the box).

  // todo possible others for convenience.

  void reset() { c_pos_ = point2d(x_beg_, x_end_); }

  point2d &operator*() { return c_pos_; }

  box_iterator &operator++() {
    if (c_pos_.x < x_end_ - 1) {
      c_pos_.x++;
    } else if (c_pos_.x == x_end_ - 1 && c_pos_.y < y_end_ - 1) {
      c_pos_.y++;
      c_pos_.x = x_beg_;
    }

    return *this;
  }

  bool operator==(const box_iterator &o) const {
    return o.c_pos_.x == c_pos_.x && o.c_pos_.y == c_pos_.y;
  }

  bool operator!=(const box_iterator &o) const {
    return o.c_pos_.x != c_pos_.x || o.c_pos_.y != c_pos_.y;
  }

  // Convenience functions.
  point2d get_c_pos() const { return c_pos_; }

  // is_done returns true if the current positions
  // corresponds to the end position.
  bool is_done() const { return c_pos_.x == x_end_ && c_pos_.y == y_end_; }

protected:
  coord x_beg_, x_end_, y_beg_, y_end_;
  point2d c_pos_;
};

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

  explicit storage(size_t n) { reserve(n); }

  storage(const storage &other) {
    size_t length = other.matrix.size();
    for (size_t i = 0; i < length; ++i) {
      matrix.push_back(other.matrix[i]);
    }
    square = other.square;
  }

  storage &operator=(const storage &s) {
    square = s.square;
    matrix = s.matrix;
  }

  coord max_coord() const { return square; }

  bool has_point(const point2d &p) const {
    return p.x < square && p.y < square;
  }

  void reserve(size_t n) {
    unsigned new_square = std::sqrt(n);

    if (n != new_square * new_square) {
      throw std::runtime_error("Wrong number (" + std::to_string(n) +
                               "): number of elements must be a square number");
    }
    square = new_square;
    matrix.reserve(n);
  }

  void resize(size_t n) {
    unsigned new_square = std::sqrt(n);

    if (n != new_square * new_square) {
      throw std::runtime_error("Wrong number (" + std::to_string(n) +
                               "): number of elements must be a square number");
    }
    square = new_square;
    matrix.resize(n);
  }

  T &get_point(size_t x, size_t y) {
    size_t pos = x + y * square;
    if (pos > square * square)
      throw std::runtime_error("Non-existing element");
    return matrix[x + y * square];
  }

  T &operator()(point2d point) { return get_point(point.x, point.y); }

  T *get_storage() { return matrix; };

protected:
  std::vector<T> matrix;
  size_t square;
};
