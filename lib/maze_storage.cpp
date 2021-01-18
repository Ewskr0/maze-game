#include <cmath>

#include "coordinate.cpp"
#include "gameplay.cpp"
#include "iterator.cpp"
#include "storage.cpp"

using maze_storage = storage<field_ptr>;

class maze : public maze_storage {
public:
  maze(const std::string &maze_str) : maze_storage(maze_str.length()) {
    for (int i = 0; i < square; i++) {
      for (int j = 0; j < square; j++) {
        size_t pos = i + j * square;
        matrix[pos] = to_field(maze_str[pos]);
      }
    }
  }
};
