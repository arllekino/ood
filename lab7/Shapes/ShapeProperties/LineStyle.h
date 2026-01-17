#pragma once

#include "../../Color/Color.h"

struct LineStyle
{
    Color color;
    unsigned width;

    bool operator==(const LineStyle& rhs) const
    {
        return color == rhs.color && width == rhs.width;
    }
};