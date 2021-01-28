#pragma once

#include "coordinate.hpp"
#include "fields.hpp"
#include "maze_storage.hpp"

class player {
public:
  player(bool isAi, point2d start_pos);

  void move(point2d new_pos);

  void displayHP();

  bool isAlive();

  void applyFieldEffect(field_effect f);

  void observe(maze m_maze);

  // Moves the player position and applies damages.
  field_ptr move(maze m_maze);

  bool ai;
  size_t hp;
  point2d pos = point2d(0, 0);
};
