#include "coordinate.hpp"

class Player {
  public:
  Player(bool isAi, point2d start_pos) {
    hp = 100;
    ai = isAi;
    pos = start_pos;
  }

  void move(point2d new_pos) {
    pos = new_pos;
  }

  bool ai;
  unsigned hp;
  point2d pos = point2d(0,0);
};
