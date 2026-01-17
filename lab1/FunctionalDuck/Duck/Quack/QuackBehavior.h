#pragma once
#include <functional>
#include <iostream>
#include <ostream>

using QuackBehavior = std::function<void()>;

inline QuackBehavior CreateMuteQuackBehavior()
{
    return []() {};
}

inline QuackBehavior CreateDefaultQuackBehavior()
{
    return []() {
        std::cout << "Quack Quack" << std::endl;
    };
}