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

  // Get maze string.
  std::string maze_str = parseFile(argv[1]);


  // Init maze.
  maze m_maze(maze_str);
  if (&m_maze == NULL)
    throw "Error during initialization.";
  m_maze.display();

  return 0;
}