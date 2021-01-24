#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

enum movement_direction {
  UP = 'w',
  LEFT = 'a',
  DOWN = 's',
  RIGHT = 'd',
  NONE = 'X'
};

std::string parseFile(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw "Could not open file";
  }

  std::string str((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

  return str;
}

// Displays possible movements.
void displayMovements() {
  std::string movements = "W: up,  A:left,  S: down, D: right";
  std::cout << movements << std::endl;
}

// Returns player's direction.
movement_direction getDirection() {
  movement_direction direction = movement_direction::NONE;
  std::cout << "Press a valid key to continue..." << std::endl;
  do {
    switch (getchar()) {
    case 'w':
    case 'W':
      direction = movement_direction::UP;
      break;
    case 'a':
    case 'A':
      direction = movement_direction::LEFT;
      break;
    case 's':
    case 'S':
      direction = movement_direction::DOWN;
      break;
    case 'd':
    case 'D':
      direction = movement_direction::RIGHT;
      break;
    default:
      break;
    }

  } while (direction == movement_direction::NONE);
  return direction;
}

// Displays the initial decription.
void displayDescription() {
  std::string description =
      "==================== Maze Game ====================\n"
      "I: entrance,    O: exit,       P: current position,\n"
      "w: wall         t: small trap, T: large trap,\n"
      "H: hidden trap, x: fog,      ' ': path\n"
      "===================================================\n";
  std::cout << description << std::endl;
}

// Displays the win message.
void displayWinMessage() {
  std::string description =
      "==================== Maze Game ====================\n"
      "                    Player won !\n"
      "===================================================\n";
  std::cout << description << std::endl;
}

// Displays the loose message.
void displayLooseMessage() {
  std::string description =
      "==================== Maze Game ====================\n"
      "                    Player is dead !!\n"
      "===================================================\n";
  std::cout << description << std::endl;
}
