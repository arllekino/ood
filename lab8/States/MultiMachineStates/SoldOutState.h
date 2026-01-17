#pragma once
#include <iostream>

#include "../../GumballMachines/IGumballMachine/IMultiGumballMachine.h"

class SoldOutState : public IReplenishableState
{
public:
    explicit SoldOutState(IMultiGumballMachine& gumballMachine)
        : m_gumballMachine(gumballMachine)
    {
    }

    void Replenish(unsigned count) override
    {
        m_gumballMachine.Replenish(count);
        if (count > 0)
        {
            if (m_gumballMachine.GetQuartersCount() > 0)
            {
                m_gumballMachine.SetHasQuarterState(); // Есть монеты -> HasQuarter
            }
            else
            {
                m_gumballMachine.SetNoQuarterState(); // Нет монет -> NoQuarter
            }
        }
    }

    void InsertQuarter() override
    {
        std::cout << "You can't insert a quarter, the machine is sold out\n";
    }

    void EjectQuarter() override
    {
        if (m_gumballMachine.GetQuartersCount() != 0)
        {
            m_gumballMachine.EjectQuarter();
            std::cout << "Quarter returned\n";
        }
        else
        {
            std::cout << "You can't eject, you haven't inserted a quarter yet\n";
        }
    }

    void TurnCrank() override
    {
        std::cout << "You turned but there's no gumballs\n";
    }

    void Dispense() override
    {
        std::cout << "No gumball dispensed\n";
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "sold out";
    }

private:
    IMultiGumballMachine& m_gumballMachine;
};
