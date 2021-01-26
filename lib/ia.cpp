
#include <unistd.h>
#include <iostream>

#include "player.cpp"
#include "maze_storage.cpp"

bool free_field(size_t y, size_t x, maze *m_maze)
{
    field *cell = m_maze->getField(point2d(x, y)).get();
    std::cout << "check if free cell, x: " << x << " y:  " << y << std::endl;

    if (cell->to_char() == field_type::PATH || cell->to_char() == field_type::EXIT)
    {
        std::cout << "is free, x: " << x << " y:  " << y << std::endl;

        return true;
    }
    std::cout << "not free, x: " << x << " y:  " << y << std::endl;
    return false;
}

bool solve(maze *m_maze, player m_player)
{
    // If you want progressive update, uncomment these lines...
    m_maze->display(m_player.pos, true);
    usleep(5000);

    // Check if we have reached our goal.
    field *cell = m_maze->getField(m_player.pos).get();
    if (cell->to_char() == field_type::EXIT)
    {
        return true;
    }

    cell->set(field_type::PLAYER);

    point2d pos = m_player.pos;

    std::cout << "current cell, x: " << pos.x << " y:  " << pos.y << std::endl;

    // Recursively search for exit.
    if (m_player.pos.x > 0 && free_field(pos.y, pos.x - 1, m_maze))
    {
        player new_player = m_player;
        new_player.pos.x--;
        std::cout << "go to cell, x: " << new_player.pos.x << " y:  " << new_player.pos.y << std::endl;

        if (solve(m_maze, new_player))
            return true;
    }
    if (m_player.pos.x < (int)m_maze->getSquare() && free_field(pos.y, pos.x + 1, m_maze))
    {
        player new_player = m_player;
        new_player.pos.x++;
        if (solve(m_maze, new_player))
            return true;
    }
    if (m_player.pos.y > 0 && free_field(pos.y - 1, pos.x, m_maze))
    {
        player new_player = m_player;
        new_player.pos.y--;
        if (solve(m_maze, new_player))
            return true;
    }
    if (m_player.pos.y < (int)m_maze->getSquare() && free_field(pos.y + 1, pos.x, m_maze))
    {
        player new_player = m_player;
        new_player.pos.y++;
        if (solve(m_maze, new_player))
            return true;
    }

    cell->set(field_type::PATH);
    return false;
}