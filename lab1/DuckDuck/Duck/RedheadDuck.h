#pragma once
#include "Duck.h"
#include "Dance/DanceMenuet.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"

class RedheadDuck final : public Duck
{
public:
    RedheadDuck()
        : Duck(
            std::make_unique<FlyWithWings>(),
            std::make_unique<QuackBehavior>(),
            std::make_unique<DanceMenuet>())
    {
    }

    void Display() const override
    {
        std::cout << "I'm redhead duck" << std::endl;
    }
};
