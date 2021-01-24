
#include "iterator.cpp"
#include "maze_storage.cpp"

class maze_iterator : public box_iterator {
public:
  maze_iterator() = delete;
  // Note that the pointer passed as argument is NON-OWNING
  // an has to exist at least as long as the iterator
  maze_iterator(const maze_storage *ms)
      : box_iterator(point2d(0, 0), point2d(0, 0)) {
    if (ms == NULL) {
      throw "Maze storage is null";
    }

    ms_ = ms;
  }
  // Without further info, the maze_iterator iterates over the entire maze
  // todo

  maze_iterator(coord x_beg, coord x_end, coord y_beg, coord y_end,
                point2d c_pos, const maze_storage *ms)
      : box_iterator(point2d(0, 0), point2d(0, 0)) {}
  // Here we want to respect the box
  // We also allow to set the current pos as this might be
  // useful later on
  // todo

  maze_iterator(const maze_iterator &other) = default;
  maze_iterator &operator=(const maze_iterator &other) = default;

  bool operator==(const maze_iterator &o) const { return true; }
  // todo
  bool operator!=(const maze_iterator &other) const { return true; }
  // todo

  void reset() { ms_ = NULL; }
  // todo
  maze_iterator &operator++() { return *this; }

  // todo
  std::pair<point2d, field_ptr> operator*() const;

  // todo

private:
  const maze_storage *ms_;
  // Maybe a private helper function?
};
