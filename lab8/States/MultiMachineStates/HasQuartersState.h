#pragma once

#include "../../GumballMachines/IGumballMachine/IMultiGumballMachine.h"
#include <iostream>

#include "../IState/IReplenishableState.h"

class HasQuarterState : public IReplenishableState
{
public:
    explicit HasQuarterState(IMultiGumballMachine& gumballMachine)
        : m_gumballMachine(gumballMachine)
    {
    }

    void Replenish(unsigned count) override
    {
        m_gumballMachine.Replenish(count);
    }

    void InsertQuarter() override
    {
        if (m_gumballMachine.GetQuartersCount() < m_gumballMachine.GetMaxQuartersCount())
        {
            std::cout << "You inserted a quarter\n";
            m_gumballMachine.InsertQuarter();
        }
        else
        {
            std::cout << "You can't insert more quarter than " << m_gumballMachine.GetMaxQuartersCount() << std::endl;
        }
    }

    void EjectQuarter() override
    {
        std::cout << "Quarter returned\n";
        m_gumballMachine.EjectQuarter();
        if (m_gumballMachine.GetQuartersCount() == 0)
        {
            m_gumballMachine.SetNoQuarterState();
        }
    }

    void TurnCrank() override
    {
        std::cout << "You turned...\n";
        m_gumballMachine.SetSoldState();
    }

    void Dispense() override
    {
        std::cout << "No gumball dispensed\n";
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "waiting for turn of crank";
    }

private:
    IMultiGumballMachine& m_gumballMachine;
};
