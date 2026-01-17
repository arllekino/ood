#pragma once
#include "Duck.h"

class DecoyDuck final : public Duck
{
public:
    DecoyDuck()
        : Duck(
            CreateFlyNoWayBehavior(),
            CreateMuteQuackBehavior(),
            CreateDanceNothingBehavior())
    {
    }

    void Display() const override
    {
        std::cout << "I'm decoy Duck" << std::endl;
    }
};
