#pragma once
#include <string>

#include "Position.h"
#include "../Path/Path.h"

struct InsertImageParameters
{
    std::optional<Position> pos;
    unsigned width;
    unsigned height;
    Path path;
};
