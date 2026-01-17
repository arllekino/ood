#pragma once

#include "../../Color/Color.h"

struct FillStyle
{
    Color color;

    bool operator==(const FillStyle &other) const
    {
        return color == other.color;
    }
};