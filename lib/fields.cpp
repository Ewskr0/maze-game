#include <memory>
#include <string>

#include "fields.hpp"

std::string field_state_to_string(field_state f) {
  switch (f) {
  case field_state::NONE:
    return "NONE";
    break;
  case field_state::FREE:
    return "FREE";
    break;
  case field_state::ENTRANCE:
    return "ENTRANCE";
    break;
  case field_state::EXIT:
    return "EXIT";
    break;
  case field_state::DAMAGING:
    return "DAMAGING";
    break;
  case field_state::DEADLY:
    return "DEADLY";
    break;
  case field_state::BLOCKED:
    return "BLOCKED";
    break;
  default:
    return "INALID";
    break;
  }
}

char field::to_char() const { return c_; }
void field::set(char c) const { c_ = c; }

void field::set_visited() const {
  if (visited_)
    return;
  visited_ = true;
}

bool field::visited() const { return visited_; }

// A function which converts a char to a shared pointer to a field
// This function will be useful to generate a maze from a string
field_ptr to_field(char c) {
  switch (c) {
  case field_type::WALL:
    return std::make_unique<wall>(wall());
  case field_type::ENTRANCE:
    return std::make_unique<maze_entrance>(maze_entrance());
  case field_type::EXIT:
    return std::make_unique<maze_exit>(maze_exit());
  case field_type::SMALL_TRAP:
    return std::make_unique<small_trap>(small_trap());
  case field_type::LARGE_TRAP:
    return std::make_unique<large_trap>(large_trap());
  case field_type::HIDDEN_TRAP:
    return std::make_unique<hidden_trap>(hidden_trap());
  default:
    return std::make_unique<path>(path());
  }
}
