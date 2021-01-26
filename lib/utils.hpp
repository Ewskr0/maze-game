#pragma once

#include <string>

enum movement_direction {
  UP = 'w',
  LEFT = 'a',
  DOWN = 's',
  RIGHT = 'd',
  NONE = 'X'
};

std::string parseFile(std::string path);
void displayMovements();
movement_direction getDirection();
void displayDescription();
void displayWinMessage();
void displayLooseMessage();
