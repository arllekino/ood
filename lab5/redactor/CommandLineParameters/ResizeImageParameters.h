#pragma once

#include "Position.h"

struct ResizeImageParameters
{
    Position pos;
    unsigned width;
    unsigned height;

    void operator=(const ResizeImageParameters& other)
    {
        pos = other.pos;
        width = other.width;
        height = other.height;
    }
};