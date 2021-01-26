#include "coordinate.hpp"

point2d operator+(const point2d &p, const offset2d &o) {
  return point2d({p.x + o.dx, p.y + o.dy});
}

point2d operator+(const offset2d &o, const point2d &p) {
  return point2d({p.x + o.dx, p.y + o.dy});
}

point2d operator-(const point2d &p, const offset2d &o) {
  return point2d({p.x - o.dx, p.y - o.dy});
}

point2d operator-(const offset2d &o, const point2d &p) {
  return point2d({o.dx - p.x, o.dy - p.y});
}

offset2d operator-(const point2d &p1, const point2d &p2) {
  return offset2d({p1.x - p2.x, p1.y - p2.y});
}
