
#include <iostream>
#include <unistd.h>

#include "ia.hpp"
#include "maze_storage.hpp"
#include "player.hpp"

bool free_field(size_t y, size_t x, maze *m_maze) {
  field *cell = m_maze->getField(point2d(x, y)).get();

  if (cell->to_char() == field_type::PATH ||
      cell->to_char() == field_type::EXIT)
    return true;
  return false;
}

bool solve(maze *m_maze, player m_player) {
  // If you want progressive update, uncomment these lines...
  m_maze->display(m_player.pos, true);

  // Check if we have reached our goal.
  field *cell = m_maze->getField(m_player.pos).get();
  if (cell->to_char() == field_type::EXIT) {
    return true;
  }

  cell->set(field_type::IA);
  point2d pos = m_player.pos;

  // Recursively search for exit.
  if (m_player.pos.x > 0 && free_field(pos.y, pos.x - 1, m_maze)) {
    player new_player = m_player;
    new_player.pos.x--;
    if (solve(m_maze, new_player))
      return true;
  }
  if (m_player.pos.x < (int)m_maze->getSquare() &&
      free_field(pos.y, pos.x + 1, m_maze)) {
    player new_player = m_player;
    new_player.pos.x++;
    if (solve(m_maze, new_player))
      return true;
  }
  if (m_player.pos.y > 0 && free_field(pos.y - 1, pos.x, m_maze)) {
    player new_player = m_player;
    new_player.pos.y--;
    if (solve(m_maze, new_player))
      return true;
  }
  if (m_player.pos.y < (int)m_maze->getSquare() &&
      free_field(pos.y + 1, pos.x, m_maze)) {
    player new_player = m_player;
    new_player.pos.y++;
    if (solve(m_maze, new_player))
      return true;
  }

  cell->set(field_type::PATH);
  return false;
}
