#pragma once
#include <iostream>
#include <ostream>

#include "IQuackBehavior.h"

class SqueakBehavior final : public IQuackBehavior
{
public:
    void Quack() override
    {
        std::cout << "Squeak!!!" << std::endl;
    }
};