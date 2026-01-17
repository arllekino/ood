#pragma once

struct IReplenishable
{
    virtual void Replenish(unsigned count) = 0;
    virtual ~IReplenishable() = default;
};