#pragma once

#include "../../GumballMachines//IGumballMachine/IMultiGumballMachine.h"
#include <iostream>

class NoQuarterState : public IReplenishableState
{
public:
    explicit NoQuarterState(IMultiGumballMachine& gumballMachine)
        : m_gumballMachine(gumballMachine)
    {
    }

    void Replenish(unsigned count) override
    {
        m_gumballMachine.Replenish(count);
    }

    void InsertQuarter() override
    {
        std::cout << "You inserted a quarter\n";
        m_gumballMachine.InsertQuarter();
        m_gumballMachine.SetHasQuarterState();
    }

    void EjectQuarter() override
    {
        std::cout << "You haven't inserted a quarter\n";
    }

    void TurnCrank() override
    {
        std::cout << "You turned but there's no quarter\n";
    }

    void Dispense() override
    {
        std::cout << "You need to pay first\n";
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "waiting for quarter";
    }

private:
    IMultiGumballMachine& m_gumballMachine;
};
