#include <functional>

#include "coordinate.hpp"
#include "iterator.hpp"

void box_iterator::reset() { c_pos_ = point2d(x_beg_, x_end_); }

point2d box_iterator::get_c_pos() const { return c_pos_; }

bool box_iterator::is_done() const {
  return c_pos_.x == x_end_ && c_pos_.y == y_end_;
}
