#include <iostream>

#include "coordinate.hpp"
#include "iterator.cpp"
#include "utils.cpp"

class player {
public:
  player(bool isAi, point2d start_pos) {
    hp = 100;
    ai = isAi;
    pos = start_pos;
  }

  void move(point2d new_pos) { pos = new_pos; }

  void displayHP() { std::cout << "HP: " << hp << std::endl; }

  bool isAlive() { return hp > 0; }

  void applyFieldEffect(field_effect f) {
    switch (f.state) {
    case field_state::DEADLY:
      hp = 0;
      break;
    case field_state::DAMAGING:
      hp -= f.damage;
      break;
    default:
      break;
    }
  }

  void observe(maze m_maze) {
    point2d lower_left(pos.x - 2, pos.y - 2);

    if (lower_left.x < 0) {
      lower_left.x = 0;
    }

    if (lower_left.y < 0) {
      lower_left.y = 0;
    }

    point2d upper_right(pos.x + 2, pos.y + 2);

    coord max = m_maze.max_coord();

    if (upper_right.x > max) {
      upper_right.x = max;
    }

    if (upper_right.y > max) {
      upper_right.y = max;
    }

    for (coord i = lower_left.y; i < upper_right.y; i++) {
      for (coord j = lower_left.x; j < upper_right.x; j++) {
        field_ptr field = m_maze.getField(point2d(j, i));
        offset2d offset = operator-(pos, point2d(j, i));
        field_effect effect = field.get()->effect(offset);
        applyFieldEffect(effect);
      }
    }
  }

  // Moves the player position and applies damages.
  field_ptr move(maze m_maze) {
    movement_direction direction;
    bool player_moved = false;
    field_ptr m_field;
    displayMovements();

    do {
      direction = getDirection();

      switch (direction) {
      case movement_direction::UP:
        pos.y--;
        break;
      case movement_direction::LEFT:
        pos.x--;
        break;
      case movement_direction::DOWN:
        pos.y++;
        break;
      case movement_direction::RIGHT:
        pos.x++;
        break;
      default:
        break;
      }

      m_field = m_maze.getField(pos);
      if (m_field.get()->to_char() != field_type::WALL) {
        player_moved = true;
        observe(m_maze);
      } else {
        std::cout << "This cell is blocked." << std::endl;
      }
    } while (!player_moved);

    return m_field;
  }

  bool ai;
  unsigned hp;
  point2d pos = point2d(0, 0);
};
