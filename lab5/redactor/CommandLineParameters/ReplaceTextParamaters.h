#pragma once
#include <string>

#include "Position.h"

struct ReplaceTextParameters
{
    Position pos;
    std::string text;

    void operator=(const ReplaceTextParameters& other)
    {
        pos = other.pos;
        text = other.text;
    }
};
