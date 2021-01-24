#include <iostream>

#include "fields.cpp"
#include "storage.cpp"

using maze_storage = storage<field_ptr>;

class maze : public maze_storage {
public:
  maze(const std::string &maze_str) : maze_storage(maze_str.length()) {
    field_ptr cell;
    for (size_t i = 0; i < square; i++) {
      for (size_t j = 0; j < square; j++) {
        size_t pos = i * square + j;
        field_ptr cell = to_field(maze_str[pos]);
        if (cell.get()->to_char() == field_type::ENTRANCE) {
          entrance_position = point2d(j, i);
        }
        matrix.push_back(cell);
      }
    }
  }

  // Returns the filed according to the player position.
  field_ptr getField(point2d player) {
    size_t pos = player.y * square + player.x;
    return matrix[pos];
  }

  // Displays the maze.
  void display(point2d player) {
    std::string buff;
    for (size_t i = 0; i < square; i++) {
      for (size_t j = 0; j < square; j++) {
        size_t pos = i * square + j;

        if (player.operator==(point2d(j, i)))
          buff.push_back(field_type::PLAYER);
        else if (operator-(player, point2d(j, i)).norm() > 2)
          buff.push_back(field_type::FOG);
        else
          buff.push_back(matrix[pos].get()->to_char());
        buff.push_back(' ');
      }
      buff.push_back('\n');
    }
    std::cout << buff << std::endl;
  }

  point2d entrance_position = point2d(0, 0);
};
