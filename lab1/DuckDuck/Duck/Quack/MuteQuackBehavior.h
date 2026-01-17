#pragma once

#include "IQuackBehavior.h"

class MuteQuackBehavior final : public IQuackBehavior
{
public:
    void Quack() override {}
};