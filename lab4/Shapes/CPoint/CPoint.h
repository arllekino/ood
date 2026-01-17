#pragma once

struct CPoint
{
    float x = 0.0;
    float y = 0.0;

    bool operator==(const CPoint& other) const
    {
        return x == other.x && y == other.y;
    }

    CPoint operator+(const CPoint& other) const
    {
        return CPoint(x + other.x, y + other.y);
    }

    CPoint& operator+=(const CPoint& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
};