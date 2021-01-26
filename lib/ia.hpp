#pragma once

#include <unistd.h>

#include "maze_storage.hpp"
#include "player.hpp"

bool free_field(size_t y, size_t x, maze *m_maze);
bool solve(maze *m_maze, player m_player);
