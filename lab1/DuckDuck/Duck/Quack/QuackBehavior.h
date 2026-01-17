#pragma once

#include <iostream>

#include "IQuackBehavior.h"

class QuackBehavior final : public IQuackBehavior
{
public:
    void Quack() override
    {
        std::cout << "Quack Quack!!!" << std::endl;
    }
};