
#pragma once

namespace math
{
    struct Point
    {
        Point()
        { }

        Point(int x, int y)
            : x(x),
              y(y)
        { }

        Point(float x, float y)
            : x(x),
              y(y)
        { }

        int x = 0;
        int y = 0;
    };

    inline Point operator + (const math::Point& left, const math::Point& right)
    {
        return math::Point(left.x + right.x, left.y + right.y);
    }

    inline Point operator - (const math::Point& left, const math::Point& right)
    {
        return math::Point(left.x - right.x, left.y - right.y);
    }

    inline Point operator / (const math::Point& left, int value)
    {
        return math::Point(left.x / value, left.y / value);
    }
}
