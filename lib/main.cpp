#include <cstddef>
#include <iostream>

#include "maze_storage.cpp"
#include "player.cpp"
#include "utils.cpp"


void displayDescription(){
  std::string description =
  "==================== Maze Game ====================\n"
  "I: entrance,    O: exit,       P: current position,\n"
  "w: wall         t: small trap, T: large trap,\n" 
  "H: hidden trap, x: fog,      ' ': path\n" 
  "===================================================\n";
  std::cout << description << std::endl;
}


int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "No file." << std::endl;
    return 1;
  }
  
  displayDescription();

  // Get maze string.
  std::string maze_str = parseFile(argv[1]);

  // Init maze.
  maze m_maze(maze_str);
  // init player
  Player player(false, m_maze.entrance_position);

  m_maze.display(player.pos);

  return 0;
}
