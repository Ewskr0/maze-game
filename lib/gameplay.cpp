#include "coordinate.cpp"

// !! ATTENTION !!//
// Copy your code from Part 1 here!
// !! ATTENTION !!//

// An enumeration of all possible
// states a field can have
// Note: The order of the definition of the different states
//       is relevant, look it up!
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

// To properly describe the effects,
// we need to keep track of the (accumulated) damage
// AND the state
// We is it sufficient to have one member variable of
// type field_state?
struct field_effect
{
  field_effect& operator+=(const field_effect& other)
  {
    //todo
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
class maze_entrance : public  field
{
public:
   maze_entrance();
// todo
};

class maze_exit : public  field
{
  // todo
};

class wall : public  field
{
public:
  // todo
};


class path : public  field
{
public:
  // todo
};


class small_trap : public  field
{
public:
  // todo
};

class large_trap : public  field
{
public:
  // todo
};


class hidden_trap : public  field
{
public:
  // todo
};

using field_ptr = std::shared_ptr<field>;

// A function which converts a char to a shared pointer to a field
// This function will be useful to generate a maze from a string
field_ptr  to_field(char c)
{
  // todo
}
//fields.h stop

