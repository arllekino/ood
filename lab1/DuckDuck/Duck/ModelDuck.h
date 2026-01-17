#pragma once

#include "Duck.h"
#include "Dance/DanceNothing.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"

class ModelDuck final : public Duck {
public:
    ModelDuck()
        : Duck(
            std::make_unique<FlyWithWings>(),
            std::make_unique<QuackBehavior>(),
            std::make_unique<DanceNothing>())
    {
    }

    void Display() const override
    {
        std::cout << "I'm model duck" << std::endl;
    }
};
