#include <functional>
#include "gameplay.cpp"
#include "coordinate.cpp"


// !! ATTENTION !!//
// Copy your code from Part 1 here!
// !! ATTENTION !!//

class box_iterator
{
public:
  // The following is not strictly necessary for our code
  // however if you want to have an iterator confirming to the
  // c++ standard you need this.
  using iterator_category = std::forward_iterator_tag;
  using value_type = point2d;
  // Has no sense for forward iterators but must be specified for
  // certain platforms in order to compile (g++ for instance)
  using difference_type = void;
  using pointer = point2d*;
  using reference = point2d&;

  box_iterator(coord x_beg, coord x_end,
               coord y_beg, coord y_end);
  // todo

  // todo possible other ctors for convenience

  box_iterator(const point2d& lower_left, const point2d& upper_right);
  // todo
  // Create the box from the lower_left corner (belongs to the box)
  // and the upper_right corner (just outside the box)

  // todo possible others for convenience

  void reset();

  box_iterator& operator++();

  bool operator==(const box_iterator& o) const;

  bool operator!=(const box_iterator& o) const;

  // Dereference : use the operator*() to generate a point
  // from current iterator

  // Convenience functions
  point2d get_c_pos() const;
  // is_done returns true if the current positions
  // corresponds to the end position
  bool is_done() const;

protected:
  coord x_beg_,
        x_end_,
        y_beg_,
        y_end_;
  point2d c_pos_;
};