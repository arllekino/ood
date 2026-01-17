#pragma once
#include "IState.h"
#include "../../GumballMachines/IGumballMachine/IReplenishable.h"

struct IReplenishableState : public IState, public IReplenishable
{
};
