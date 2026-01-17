#pragma once
#include "Duck.h"

class RubberDuck final : public Duck
{
public:
    RubberDuck() : Duck(
        CreateFlyWithWingsBehavior(),
        CreateDefaultQuackBehavior(),
        CreateDanceNothingBehavior())
    {
    }

    void Display() const override
    {
        std::cout << "I'm rubber duck" << std::endl;
    }
};
