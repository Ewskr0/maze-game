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
};
