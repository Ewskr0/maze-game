#include <iostream>

#include "coordinate.hpp"

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

  bool ai;
  unsigned hp;
  point2d pos = point2d(0, 0);
};
