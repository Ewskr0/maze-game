#include <cstddef>
#include <iostream>
#include <utility>

#include "maze_storage.cpp"
#include "player.cpp"
#include "utils.cpp"

// Moves the player position and applies damages.
field_ptr movePlayer(maze m_maze, player *m_player) {
  movement_direction direction;
  bool player_moved = false;
  field_ptr m_field;
  point2d m_pos = point2d(0, 0);
  displayMovements();

  do {
    m_pos = m_player->pos;
    direction = getDirection();

    switch (direction) {
    case movement_direction::UP:
      m_pos.y--;
      break;
    case movement_direction::LEFT:
      m_pos.x--;
      break;
    case movement_direction::DOWN:
      m_pos.y++;
      break;
    case movement_direction::RIGHT:
      m_pos.x++;
      break;
    default:
      break;
    }

    m_field = m_maze.getField(m_pos);
    if (m_field.get()->to_char() != field_type::WALL) {
      player_moved = true;
      m_player->pos = m_pos;
      field_effect effect = m_field.get()->effect();
      std::cout << "effect: " << field_state_to_string(effect.state)
                << std::endl;
      m_player->applyFieldEffect(effect);

    } else {
      std::cout << "This cell is blocked." << std::endl;
    }
  } while (!player_moved);

  return m_field;
}

// PLays until the player wins or dies.
void startGame(maze m_maze, player *m_player) {
  bool isPlaying = true;
  field_ptr cell_type;

  do {
    m_player->displayHP();
    m_maze.display(m_player->pos);

    cell_type = movePlayer(m_maze, m_player);
    isPlaying =
        m_player->isAlive() && cell_type.get()->to_char() != field_type::EXIT;

  } while (isPlaying);

  m_maze.display(m_player->pos);
  if (m_player->isAlive()) {
    displayWinMessage();
  } else {
    displayLooseMessage();
  }
}

// Init the maze and the player.
std::pair<maze, player> initGame(char const *file_path) {
  displayDescription();
  std::string maze_str = parseFile(file_path);
  maze m_maze(maze_str);
  player m_player(false, m_maze.entrance_position);
  return std::make_pair(m_maze, m_player);
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "No file." << std::endl;
    return 1;
  }

  std::pair<maze, player> init = initGame(argv[1]);
  startGame(init.first, &init.second);

  return 0;
}
