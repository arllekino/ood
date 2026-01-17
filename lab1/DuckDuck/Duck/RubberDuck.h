#pragma once
#include "Duck.h"
#include "Dance/DanceNothing.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"

class RubberDuck final : public Duck
{
public:
    RubberDuck() : Duck(
        std::make_unique<FlyWithWings>(),
        std::make_unique<QuackBehavior>(),
        std::make_unique<DanceNothing>())
    {
    }

    void Display() const override
    {
        std::cout << "I'm rubber duck" << std::endl;
    }
};
