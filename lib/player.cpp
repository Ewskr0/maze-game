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
    coord llx = pos.x - 2;
    coord lly = pos.y - 2;

    if (llx < 0) {
      llx = 0;
    }

    if (lly < 0) {
      lly = 0;
    }

    coord urx = pos.x + 2;
    coord ury = pos.y + 2;

    coord max = m_maze.max_coord();

    if (urx > max) {
      urx = max;
    }

    if (ury > max) {
      ury = max;
    }

    point2d lower_left(llx, lly);
    point2d upper_right(urx, ury);

    box_iterator it(lower_left, upper_right);
    point2d itpos = *it;
    for (; *it != upper_right; ++it) {
      field_ptr field = m_maze.getField(itpos);
      if (field.get()->to_char() == field_type::LARGE_TRAP) {
        field_effect effect = field.get()->effect(/* offset */);
        applyFieldEffect(effect);
      }
    }
  }

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
        field_effect effect = m_field.get()->effect();
        applyFieldEffect(effect);
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
