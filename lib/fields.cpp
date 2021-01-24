#include <memory>
#include <string>

#include "coordinate.hpp"

enum class field_state {
  NONE = 0,
  FREE,
  ENTRANCE,
  EXIT,
  DAMAGING,
  DEADLY,
  BLOCKED,
};

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

enum field_type {
  PATH = ' ',
  ENTRANCE = 'I',
  LARGE_TRAP = 'T',
  SMALL_TRAP = 't',
  HIDDEN_TRAP = 'H',
  WALL = 'w',
  EXIT = 'O',
  FOG = 'X',
  PLAYER = 'P',
};

struct field_effect {
  field_effect &operator+=(const field_effect &other) {
    this->damage += other.damage;
    if (other.state > this->state)
      this->state = other.state;
    return *this;
  }

  field_effect(field_state s) : state(s), damage(0) {}

  field_effect(field_state s, unsigned d) : state(s), damage(d) {}

  bool operator==(const field_effect &other) {
    return this->state == other.state && this->damage == other.damage;
  }

  bool operator!=(const field_effect &o) { return !(*this == o); }

  field_state state = field_state::NONE;
  unsigned damage = 0;
};

// Base class for all fields
// A field needs to be representable by a char
// (to print the game on the console)
// and we have to be able to evaluate its effects
// a field can effect the cell where it is located, but also surrounding cells.
// To avoid storing a fields own location, we will use the relative distance
// to the cell for which we want to evaluate effect

class field {
public:
  field(char c) : c_{c} {}

  virtual ~field() {}

  char to_char() const { return c_; }

  void set(char c) const { c_ = c; }

  // o corresponds to the distance of this field to the one for which we want
  // to evaluate
  // The boolean argument is_sim has the following role:
  // when evaluating the field for a turn of the actual game is_sim = false
  // if the AI-player evaluates the field -> is_sim is true
  // this way we can implement hidden traps that are not triggered by the AI
  virtual field_effect effect(const offset2d &o, bool is_sim = true) const = 0;

  // Helper function -> arg <-> zero offset
  field_effect effect() const { return effect({0, 0}); }

private:
  mutable char c_;
};

// Note that the constructors for the derived classes do
// not take any argument
class maze_entrance : public field {
public:
  maze_entrance() : field(field_type::ENTRANCE) {}

  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0)) {
      return field_effect(field_state::ENTRANCE);
    }
    return field_effect(field_state::NONE);
  }
};

class maze_exit : public field {
public:
  maze_exit() : field(field_type::EXIT) {}

  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0)) {
      return field_effect(field_state::EXIT);
    }
    return field_effect(field_state::NONE);
  }
};

class wall : public field {
public:
  wall() : field(field_type::WALL) {}

  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0))
      return field_effect(field_state::BLOCKED);
    return field_effect(field_state::NONE);
  }
};

class path : public field {
public:
  path() : field(field_type::PATH) {}

  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0)) {
      std::cout << "path" << std::endl;
      return field_effect(field_state::FREE);
    }
    return field_effect(field_state::NONE);
  }
};

class small_trap : public field {
public:
  small_trap() : field(field_type::SMALL_TRAP) {}

  field_effect effect(const offset2d &offset, bool is_sim = true) const {
    if (offset == offset2d(0, 0))
      return field_effect(field_state::DEADLY);
    return field_effect(field_state::NONE);
  }
};

class large_trap : public field {
public:
  large_trap() : field(field_type::LARGE_TRAP) {}

  field_effect effect(const offset2d &o, bool is_sim = true) const {
    if (o.norm() <= 1)
      return field_effect(field_state::DAMAGING, 5);
    return field_effect(field_state::NONE);
  }
};

class hidden_trap : public field {
  bool damaged = false;

public:
  hidden_trap() : field(field_type::HIDDEN_TRAP) {
    this->set(field_type::PATH);
  }

  field_effect effect(const offset2d &o, bool is_sim = true) const {
    if (o.norm() <= 1) {
      this->set(field_type::LARGE_TRAP);
      return field_effect(field_state::DAMAGING, 5);
    }
    return field_effect(field_state::NONE);
  }
};

using field_ptr = std::shared_ptr<field>;

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
