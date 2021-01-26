#include <cstddef>
#include <iostream>
#include <tuple>

#include "ia.hpp"
#include "maze_storage.hpp"
#include "player.hpp"
#include "utils.hpp"

// PLays until the player wins or dies.
void startGame(maze m_maze, player *m_player) {
  bool isPlaying = true;
  field_ptr cell_type;

  do {
    m_player->displayHP();
    m_maze.display(m_player->pos, false);
    cell_type = m_player->move(m_maze);
    isPlaying =
        m_player->isAlive() && cell_type.get()->to_char() != field_type::EXIT;
  } while (isPlaying);

  m_maze.display(m_player->pos, false);
  if (m_player->isAlive()) {
    displayWinMessage();
  } else {
    displayLooseMessage();
  }
}

// Init the maze and the player.
std::tuple<maze, player> initGame(char const *file_path, bool ia) {
  displayDescription();
  std::string maze_str = parseFile(file_path);
  maze m_maze(maze_str);
  player m_player(ia, m_maze.entrance_position);
  return std::make_tuple(m_maze, m_player);
}

void startIA(maze *m_maze, player m_player) {
  if (solve(m_maze, m_player)) {
    displayWinMessage();
  } else {
    displayLooseMessage();
  }
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "No file." << std::endl;
    return 1;
  }
  auto [m_maze, m_player] = initGame(argv[1], argc > 2);

  if (argc == 2)
    startGame(m_maze, &m_player);
  else
    startIA(&m_maze, m_player);
  return 0;
}
