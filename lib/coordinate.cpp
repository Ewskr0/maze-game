//#include <functional>

using coord = int;

// Defnes the diference between two points. Note that you should define the basic
// operations of addition and substraction between points and offsets.
struct offset2d
{
    offset2d() = delete;
    offset2d(coord dx_in, coord dy_in) : dx(dx_in), dy(dy_in){};

    offset2d(const offset2d &o) = default;
    offset2d &operator=(const offset2d &o) = default;

    // Basic operations.
    bool operator==(const offset2d &o) const
    {
        return (dx == o.dx && dy == o.dy);
    }
    bool operator!=(const offset2d &o) const
    {
        return (dx != o.dx || dy != o.dy);
    }
    bool operator<(const offset2d &o) const
    {
        return (dx < o.dx && dy < o.dy);
    }

    offset2d &operator+=(const offset2d &o)
    {
        dx += o.dx;
        dy += o.dy;
    }

    offset2d &operator-=(const offset2d &o)
    {
        dx -= o.dx;
        dy -= o.dy;
    }

    offset2d operator+(const offset2d &other) const
    {
        return offset2d({dx + other.dx, dy + other.dy});
    }
    offset2d operator-(const offset2d &other) const
    {
        return offset2d({dx - other.dx, dy - other.dy});
    }

    coord dx, dy;
};

// Defines a point in the grid, mainly a pair of coordinates.
struct point2d
{
    point2d() = delete;
    point2d(coord x_in, coord y_in) : x(x_in), y(y_in){};

    point2d(const point2d &o) = default;
    point2d &operator=(const point2d &o) = default;

    // Basic operations.
    bool operator==(const point2d &o) const
    {
        return (x == o.x && y == o.y);
    }
    bool operator!=(const point2d &o) const
    {
        return (x != o.x || y != o.y);
    }
    bool operator<(const point2d &o) const
    {
        return (x < o.x && y < o.y);
    }
    point2d &operator+=(const offset2d &o)
    {
        x += o.dx;
        y += o.dy;
    }
    point2d &operator-=(const offset2d &o)
    {
        x -= o.dx;
        y -= o.dy;
    }

    coord x, y;
};

point2d operator+(const point2d &p, const offset2d &o)
{
        return point2d({p.x+ o.dx, p.y+o.dy});
}
point2d operator+(const offset2d &o, const point2d &p)
{
        return point2d({p.x+ o.dx, p.y+o.dy});
}
point2d operator-(const point2d &p, const offset2d &o)
{
        return point2d({p.x- o.dx, p.y -o.dy});
}
point2d operator-(const offset2d &o, const point2d &p)
{
        return point2d({o.dx - p.x, o.dy - p.y});
}
offset2d operator-(const point2d &p1, const point2d &p2)
{
    return offset2d({p1.x - p2.x, p1.y - p2.y});
}

/*
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
*/
