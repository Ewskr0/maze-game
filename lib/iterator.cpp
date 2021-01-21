#include <functional>

#include "coordinate.hpp"

class box_iterator {
public:
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
