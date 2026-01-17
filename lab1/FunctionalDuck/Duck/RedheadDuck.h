#pragma once
#include "Duck.h"

class RedheadDuck final : public Duck
{
public:
    RedheadDuck()
        : Duck(
            CreateFlyWithWingsBehavior(),
            CreateDefaultQuackBehavior(),
            CreateDanceMenuetBehavior())
    {
    }

    void Display() const override
    {
        std::cout << "I'm redhead duck" << std::endl;
    }
};
