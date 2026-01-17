#pragma once
#include "Duck.h"

class MallardDuck final : public Duck
{
public:
    MallardDuck()
        : Duck(
            CreateFlyWithWingsBehavior(),
            CreateDefaultQuackBehavior(),
            CreateDanceWaltzBehavior())
    {
    }

    void Display() const override
    {
        std::cout << "I'm mallard duck" << std::endl;
    }
};
