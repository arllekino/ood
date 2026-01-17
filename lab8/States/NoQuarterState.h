#pragma once

#include "IState/IState.h"
#include "../GumballMachines//IGumballMachine/IGumballMachine.h"
#include <iostream>

class NoQuarterState : public IState
{
public:
    explicit NoQuarterState(IGumballMachine& gumballMachine)
        : m_gumballMachine(gumballMachine)
    {
    }

    void InsertQuarter() override
    {
        std::cout << "You inserted a quarter\n";
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
    IGumballMachine& m_gumballMachine;
};
