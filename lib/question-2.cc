// !! ATTENTION !!//
// Copy your code from Part 1 here!
// !! ATTENTION !!//
using coord = int;

#include <stdlib.h>
#include <algorithm>

struct offset2d
{
    offset2d() = delete;
    offset2d(coord x, coord y) : x(x), y(y)
    {
    }

    offset2d(const offset2d &o) = default;
    offset2d &operator=(const offset2d &o) = default;

    bool operator==(const offset2d &o) const
    {
        return this->x == o.x && this->y == o.y;
    }
    bool operator!=(const offset2d &o) const
    {
        return !(*this == o);
    }
    bool operator<(const offset2d &o) const
    {
        if (this->x < o.x)
            return true;
        return this->y < o.y;
    }
    offset2d &operator+=(const offset2d &o)
    {
        this->x += o.x;
        this->y += y;
        return *this;
    }
    offset2d &operator-=(const offset2d &o)
    {
        this->x -= o.x;
        this->y -= y;
        return *this;
    }

    offset2d operator+(const offset2d &other) const
    {
        return offset2d(this->x + other.x, this->y + other.y);
    }
    offset2d operator-(const offset2d &other) const
    {
        return offset2d(this->x - other.x, this->y - other.y);
    }

    unsigned uniform_norm() const
    {
        return std::max(abs(this->x), abs(this->y));
    }

    coord x,
        y;
};

struct point2d
{
    point2d() = delete;
    point2d(coord x, coord y) : x(x), y(y) {}

    point2d(const point2d &o) = default;
    point2d &operator=(const point2d &o) = default;

    bool operator==(const point2d &o) const
    {
        return this->x == o.x && this->y == o.y;
    }
    bool operator!=(const point2d &o) const
    {
        return !(*this == o);
    }
    bool operator<(const point2d &o) const
    {
        if (this->x < o.x)
            return true;
        return this->y < o.y;
    }
    point2d &operator+=(const offset2d &o)
    {
        this->x += o.x;
        this->y += o.y;
        return *this;
    }
    point2d &operator-=(const offset2d &o)
    {
        this->x -= o.x;
        this->y -= y;
        return *this;
    }
    coord x,
        y;
};

point2d operator+(const point2d &p, const offset2d &o)
{
    return point2d(p.x + o.x, p.y + o.y);
}
point2d operator+(const offset2d &o, const point2d &p)
{
    return point2d(p.x + o.x, p.y + o.y);
}
point2d operator-(const point2d &p, const offset2d &o)
{
    return point2d(p.x - o.x, p.y - o.y);
}
point2d operator-(const offset2d &o, const point2d &p)
{
    return point2d(p.x - o.x, p.y - o.y);
}

offset2d operator-(const point2d &p1, const point2d &p2)
{
    return offset2d(p1.x - p2.x, p1.y - p2.y);
}

#include <functional>

template <>
struct std::less<point2d>
{
    bool operator()(const point2d &x, const point2d &y) const { return x < y; }
};

template <>
struct std::less<offset2d>
{
    bool operator()(const offset2d &x, const offset2d &y) const { return x < y; }
};

// An enumeration of all possible
// states a field can have
// Note: The order of the definition of the different states
//       is relevant, look it up!
enum class field_state
{
    NONE = 0,
    FREE,
    DAMAGING,
    ENTRANCE,
    EXIT,
    DEADLY,
    BLOCKED,
};

// To properly describe the effects,
// we need to keep track of the (accumulated) damage
// AND the state
// Why is it sufficient to have one member variable of
// type field_state?
struct field_effect
{
    field_effect &operator+=(const field_effect &other)
    {
        this->damage += other.damage;
        if (other.state > this->state)
            this->state = other.state;
        return *this;
    }

    field_effect(field_state s) : state(s), damage(0) {}

    field_effect(field_state s, unsigned d) : state(s), damage(d) {}

    bool operator==(const field_effect &other)
    {
        return this->state == other.state && this->damage == other.damage;
    }

    bool operator!=(const field_effect &o)
    {
        return !(*this == o);
    }

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
class field
{
public:
    field(char c)
        : c_{c}
    {
    }

    virtual ~field()
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
    virtual field_effect effect(const offset2d &o, bool is_sim = true) const = 0;

    // Helper function -> arg <-> zero offset
    field_effect effect() const
    {
        return effect({0, 0});
    }

private:
    mutable char c_;
};

// Note that the constructors for the derived classes do
// not take any argument
class maze_entrance : public field
{
public:
    maze_entrance()
        : field('I') {}
    field_effect effect(const offset2d &offset, bool is_sim = true) const
    {
        if (offset == offset2d(0, 0))
            return field_effect(field_state::ENTRANCE);
        return field_effect(field_state::NONE);
    }
};

class maze_exit : public field
{
public:
    maze_exit() : field('O') {}
    field_effect effect(const offset2d &offset, bool is_sim = true) const
    {
        if (offset == offset2d(0, 0))
            return field_effect(field_state::EXIT);
        return field_effect(field_state::NONE);
    }
};

class wall : public field
{
public:
    wall() : field('w') {}
    field_effect effect(const offset2d &offset, bool is_sim = true) const
    {
        if (offset == offset2d(0, 0))
            return field_effect(field_state::BLOCKED);
        return field_effect(field_state::NONE);
    }
};

class path : public field
{
public:
    path() : field(' ') {}
    field_effect effect(const offset2d &offset, bool is_sim = true) const
    {
        if (offset == offset2d(0, 0))
            return field_effect(field_state::FREE);
        return field_effect(field_state::NONE);
    }
};

class small_trap : public field
{
public:
    small_trap() : field('t') {}
    field_effect effect(const offset2d &offset, bool is_sim = true) const
    {
        if (offset == offset2d(0, 0))
            return field_effect(field_state::DEADLY);
        return field_effect(field_state::NONE);
    }
};

class large_trap : public field
{
public:
    large_trap() : field('T') {}
    field_effect effect(const offset2d &o, bool is_sim = true) const
    {
        unsigned norm = o.uniform_norm();
        if (norm <= 1)
            return field_effect(field_state::DAMAGING, 5);
        return field_effect(field_state::NONE);
    }
};

class hidden_trap : public field
{
public:
    hidden_trap() : field(' ') {}
    field_effect effect(const offset2d &o, bool is_sim = true) const
    {
        if (is_sim && this->to_char() == ' ')
        {
            if (o == offset2d(0, 0))
                return field_effect(field_state::FREE);
            return field_effect(field_state::NONE);
        }
        unsigned norm = o.uniform_norm();
        if (norm <= 1)
        {
            return field_effect(field_state::DAMAGING, 5);
            this->set('H');
        }
        return field_effect(field_state::NONE);
    }
};

using field_ptr = std::shared_ptr<field>;

// A function which converts a char to a shared pointer to a field
// This function will be useful to generate a maze from a string
field_ptr to_field(char c)
{
    switch (c)
    {
    case ' ':
        return std::make_unique<path>(path());
    case 'w':
        return std::make_unique<wall>(wall());
    case 'I':
        return std::make_unique<maze_entrance>(maze_entrance());
    case 'O':
        return std::make_unique<maze_exit>(maze_exit());
    case 't':
        return std::make_unique<small_trap>(small_trap());
    case 'T':
        return std::make_unique<large_trap>(large_trap());
    case 'H':
        return std::make_unique<hidden_trap>(hidden_trap());
    }
    return std::unique_ptr<field>();
}
//fields.h stop
