#pragma once

#include "fields.hpp"
#include "storage.hpp"

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
  field_ptr getField(point2d player);

  // Displays the maze.
  void display(point2d player, bool ia);

  point2d entrance_position = point2d(0, 0);
};
