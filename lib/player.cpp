#include "coordinate.hpp"

class Player {
  Player(bool manual) {
    hp = 100;
    manual = manual;
  }

private:
  bool manual;
  unsigned hp;
  point2d pos;
};
