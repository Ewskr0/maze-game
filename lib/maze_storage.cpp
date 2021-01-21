#include <iostream>
#include "fields.cpp"
#include "storage.cpp"

using maze_storage = storage<field_ptr>;

class maze : public maze_storage
{
public:
  maze(const std::string &maze_str) : maze_storage(maze_str.length())
  {
    field_ptr cell;
    for (size_t i = 0; i < square; i++)
    {
      for (size_t j = 0; j < square; j++)
      {
        size_t pos = i * square + j;
        field_ptr cell = to_field(maze_str[pos]);
        if (cell.get()->to_char() == field_type::ENTRANCE)
        {
          entrance_position = point2d(i, j);
        }
        matrix.push_back(cell);
      }
    }
  }

  void display()
  {
    std::string buff;
    buff.push_back(matrix[0].get()->to_char());
    for (int i = 1; i < matrix.size(); i++)
    {
      buff.push_back(matrix[i].get()->to_char());
      if ((i + 1) % square == 0)
        buff.push_back('\n');
    }
    std::cout << buff << std::endl;
  }

  point2d entrance_position = point2d(0, 0);
};
