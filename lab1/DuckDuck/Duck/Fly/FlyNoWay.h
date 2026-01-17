#pragma once

#include "IFlyBehavior.h"

class FlyNoWay final : public IFlyBehavior
{
public:
    void Fly() override {}
};