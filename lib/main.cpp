#include <iostream>
#include <cstddef>
#include "maze_storage.cpp"
#include "utils.cpp"

int main(int argc, char const *argv[])
{
  std::cout << "Maze Game" << std::endl;

  if (argc < 2)
  {
    std::cout << "No file." << std::endl;
  }

  std::string maze_str = parseFile(argv[1]);
  std::cout << maze_str << std::endl;
  std::cout << "Maze length: " << maze_str.length() << std::endl;

  maze_storage m_maze = maze(maze_str);
  if(&m_maze == NULL)
    std::cout << "Maze initialized" << std::endl;

  return 0;
}