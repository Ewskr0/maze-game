#include <iostream>
#include <string>

#include "fields.hpp"
#include "maze_storage.hpp"
#include "storage.hpp"

field_ptr maze::getField(point2d player) {
  size_t pos = player.y * square + player.x;
  return matrix[pos];
}

void maze::display(point2d player, bool ia) {
  std::string buff;
  for (size_t i = 0; i < square; i++) {
    for (size_t j = 0; j < square; j++) {
      size_t pos = i * square + j;
      field_ptr field = getField(point2d(j, i));

      if (player.operator==(point2d(j, i))) {
        buff.push_back(field_type::PLAYER);
      } else if (!field.get()->visited() &&
                 operator-(player, point2d(j, i)).norm() > 2 && !ia) {
        buff.push_back(field_type::FOG);
      } else {
        field.get()->set_visited();
        buff.push_back(matrix[pos].get()->to_char());
      }
      buff.push_back(' ');
    }
    buff.push_back('\n');
  }
  std::cout << buff << std::endl;
}
