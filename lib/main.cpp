#include <cstddef>
#include <iostream>

#include "maze_storage.cpp"
#include "player.cpp"
#include "utils.cpp"

int main(int argc, char const *argv[]) {
  std::cout << "Maze Game" << std::endl;

  if (argc < 2) {
    std::cout << "No file." << std::endl;
    return 1;
  }

  // Get maze string.
  std::string maze_str = parseFile(argv[1]);

  // Init maze.
  maze m_maze(maze_str);
  // init player
  Player player(false, m_maze.entrance_position);

  m_maze.display(player.pos);

  return 0;
}
