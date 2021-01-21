#include <iostream>
#include "fields.cpp"
#include "storage.cpp"

using maze_storage = storage<field_ptr>;

class maze : public maze_storage
{
public:
  maze(const std::string &maze_str) : maze_storage(maze_str.length())
  {
    for (int i = 0; i < maze_str.size(); i++)
    {
      matrix.push_back(to_field(maze_str[i]));
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
};
