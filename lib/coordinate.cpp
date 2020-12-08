#include <functional>

using coord = // Suitable integral type here

struct offset2d
{
  offset2d() = delete;
  offset2d(coord dx_in, coord dy_in);
  // todo


  offset2d(const offset2d& o) = default;
  offset2d& operator=(const offset2d& o) = default;

  // todo
  bool operator==(const offset2d& o) const;
  bool operator!=(const offset2d& o) const;
  bool operator<(const offset2d& o) const;
  offset2d& operator+=(const offset2d& o);
  offset2d& operator-=(const offset2d& o);

  offset2d operator+(const offset2d& other) const;
  offset2d operator-(const offset2d& other) const;

  coord dx,
        dy;
};

struct point2d
{
  point2d() = delete;
  point2d(coord x_in, coord y_in);
  // todo

  point2d(const point2d& o) = default;
  point2d& operator=(const point2d& o) = default;

  // todo
  bool operator==(const point2d& o) const;
  bool operator!=(const point2d& o) const;
  bool operator<(const point2d& o) const;
  point2d& operator+=(const offset2d& o);
  point2d& operator-=(const offset2d& o);

  coord x,
        y;
};

// todo : Implement the functions corresponding to
// these signatures
point2d operator+(const point2d& p, const offset2d& o);
point2d operator+(const offset2d& o, const point2d& p);
point2d operator-(const point2d& p, const offset2d& o);
point2d operator-(const offset2d& o, const point2d& p);

offset2d operator-(const point2d& p1, const point2d& p2);

template <>
struct std::less<point2d>
{
  // todo : Look up where std::less is used,
  // then implement it
};

template <>
struct std::less<offset2d>
{
  // todo : Look up where std::less is used,
  // then implement it
};