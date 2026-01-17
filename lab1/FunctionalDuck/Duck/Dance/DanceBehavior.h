#pragma once
#include <functional>
#include <iostream>

using DanceBehavior = std::function<void()>;

inline DanceBehavior CreateDanceWaltzBehavior()
{
    return []() {
        std::cout << "I'm dancing waltz!" << std::endl;
    };
}

inline DanceBehavior CreateDanceMenuetBehavior()
{
    return []() {
        std::cout << "I'm dancing menuet!" << std::endl;
    };
}

inline DanceBehavior CreateDanceNothingBehavior()
{
    return []() {};
}