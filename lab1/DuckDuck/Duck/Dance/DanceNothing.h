#pragma once
#include "IDanceBehavior.h"

class DanceNothing final : public IDanceBehavior
{
public:
    void Dance() override {}
};

// выянсить и доложить для чего