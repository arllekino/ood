#pragma once
#include "IReplenishable.h"

struct IMultiGumballMachine : public IReplenishable
{
    void Replenish(unsigned count) override = 0;

    virtual void ReleaseBall() = 0;
    virtual unsigned GetBallCount() const = 0;
    virtual unsigned GetQuartersCount() const = 0;
    virtual unsigned GetMaxQuartersCount() const = 0;

    virtual void InsertQuarter() = 0;
    virtual void EjectQuarter() = 0;

    virtual void SetSoldOutState() = 0;
    virtual void SetNoQuarterState() = 0;
    virtual void SetSoldState() = 0;
    virtual void SetHasQuarterState() = 0;

    ~IMultiGumballMachine() override = default;
};
