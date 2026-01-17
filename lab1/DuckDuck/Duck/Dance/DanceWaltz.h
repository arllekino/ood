#pragma once
#include <iostream>

#include "IDanceBehavior.h"

class DanceWaltz final : public IDanceBehavior
{
public:
    void Dance() override
    {
        std::cout << "I'm dancing waltz!" << std::endl;
    }
};