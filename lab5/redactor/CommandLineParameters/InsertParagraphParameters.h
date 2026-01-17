#pragma once
#include <string>

#include "Position.h"

struct InsertParagraphParameters
{
    std::optional<Position> pos;
    std::string text;
};
