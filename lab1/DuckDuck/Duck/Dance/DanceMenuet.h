#pragma once
#include <iostream>
#include <ostream>

#include "IDanceBehavior.h"

class DanceMenuet final : public IDanceBehavior
{
public:
    void Dance() override
    {
        std::cout << "I'm dancing menuet" << std::endl;
    }
};