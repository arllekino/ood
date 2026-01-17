#pragma once

struct Point
{
    unsigned int x;
    unsigned int y;

    Point(unsigned x, unsigned y) : x(x), y(y) {}

    void operator+(const Point& other)
    {
        x += other.x;
        y += other.y;
    }

    void operator-(const Point& other)
    {
        x -= other.x;
        y -= other.y;
    }

    auto operator<=>(const Point& other) const
    {
        if (auto cmp = x <=> other.x; cmp != 0) return cmp;
        return y <=> other.y;
    }
};