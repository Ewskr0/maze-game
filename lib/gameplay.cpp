#include <memory>

#include "coordinate.cpp"

enum class field_state
{
  NONE = 0,
  FREE,
  ENTRANCE,
  EXIT,
  DAMAGING,
  DEADLY,
  BLOCKED,
};

enum field_type {
  Entrance  = 'I',
  Trap = 'T',
  Small_trap  = 't',
  Wall = 'W',
  Exit = 'O',
  Fog = 'X',
  Current_position = 'P',
  Path = ' ',
};

// To properly describe the effects,
// we need to keep track of the (accumulated) damage
// AND the state
// is it sufficient to have one member variable of
// type field_state?
struct field_effect
{

  field_effect(const int damage, field_type type)
  {
  }

  field_effect& operator+=(const field_effect& other)
  {
    switch (other.state) {
      case field_state::BLOCKED:
        break;
      case field_state::DAMAGING:
        damage += other.damage;
        break;
      case field_state::DEADLY:
        damage += 100;
        break;
      default:
        break;
    }
  }

  // todo:
  // operators are missing here

  field_state state = field_state::NONE;
  unsigned damage = 0;
};
// utils.h stop

//fields.h start
// Base class for all fields
// A field needs to be representable by a char
// (to print the game on the console)
// and we have to be able to evaluate its effects
// a field can effect the cell where it is located, but also surrounding cells.
// To avoid storing a fields own location, we will use the relative distance
// to the cell for which we want to evaluate effect
class  field
{
public:
   field(char c)
      : c_{c}
  {
  }

  virtual ~ field()
  {
  }

  char to_char() const
  {
    return c_;
  }

  void set(char c) const
  {
    c_ = c;
  }

  // o corresponds to the distance of this field to the one for which we want
  // to evaluate
  // The boolean argument is_sim has the following role:
  // when evaluating the field for a turn of the actual game is_sim = false
  // if the AI-player evaluates the field -> is_sim is true
  // this way we can implement hidden traps that are not triggered by the AI
  virtual field_effect effect(const offset2d& o, bool is_sim = true) const = 0;

  // Helper function -> arg <-> zero offset
  field_effect effect() const
  {
    return effect({0,0});
  }

private:
  mutable char c_;
};

// Note that the constructors for the derived classes do
// not take any argument
class maze_entrance : public field
{
public:
  maze_entrance() : field(field_type::Entrance) {}
  field_effect effect(const offset2d& o, bool is_sim = true)
  {
  }
};

class maze_exit : public  field
{
  maze_exit() : field(field_type::Exit) {}
};

class wall : public field
{
public:
  wall() : field(field_type::Wall) {}
};


class path : public field
{
public:
  path() : field(field_type::Path) {}
};


class small_trap : public field
{
public:
  small_trap() : field(field_type::Small_trap) {}
};

class large_trap : public field
{
public:
  large_trap() : field(field_type::Trap) {}
};


class hidden_trap : public field
{
public:
  hidden_trap() : field(field_type::Path) {}
};

using field_ptr = std::shared_ptr<field>;

// A function which converts a char to a shared pointer to a field
// This function will be useful to generate a maze from a string
field_ptr to_field(char c)
{
  return std::make_shared<field>(c);
}

//fields.h stop
