#pragma once
#include <functional>
#include <iostream>
#include <ostream>

#include "../Quack/QuackBehavior.h"

using FlyBehavior = std::function<void()>;

inline FlyBehavior CreateFlyNoWayBehavior()
{
    return []() {};
}

inline FlyBehavior CreateFlyWithWingsBehavior()
{
    return []() {
        std::cout << "I'm flying with wings!" << std::endl;
    };
}

inline FlyBehavior CreateFlyWithWingsAndQuack(const QuackBehavior& quackBehavior)
{
    return [quackBehavior, flightCount = 0]() mutable {
        std::cout << "I'm flying with wings!" << std::endl;
        flightCount++;

        if (flightCount > 0 && flightCount % 2 == 0)
        {
            quackBehavior();
        }
    };
}