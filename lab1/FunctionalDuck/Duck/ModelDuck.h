#pragma once
#include "Duck.h"

class ModelDuck final : public Duck {
public:
    ModelDuck()
        : Duck(
            CreateFlyWithWingsBehavior(),
            CreateDefaultQuackBehavior(),
            CreateDanceNothingBehavior())
    {
    }

    void Display() const override
    {
        std::cout << "I'm model duck" << std::endl;
    }
};
