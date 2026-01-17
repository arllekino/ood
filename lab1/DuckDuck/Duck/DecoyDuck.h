#pragma once
#include "Duck.h"
#include "Dance/DanceNothing.h"
#include "Fly/FlyNoWay.h"
#include "Quack/MuteQuackBehavior.h"

class DecoyDuck final : public Duck
{
public:
    DecoyDuck()
        : Duck(
            std::make_unique<FlyNoWay>(),
            std::make_unique<MuteQuackBehavior>(),
            std::make_unique<DanceNothing>())
    {
    }

    void Display() const override
    {
        std::cout << "I'm decoy Duck" << std::endl;
    }
};
