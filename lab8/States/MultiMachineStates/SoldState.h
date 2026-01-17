#pragma once
#include <iostream>

#include "../../GumballMachines/IGumballMachine/IMultiGumballMachine.h"
#include "../IState/IReplenishableState.h"

class SoldState : public IReplenishableState
{
public:
    explicit SoldState(IMultiGumballMachine& gumballMachine)
        : m_gumballMachine(gumballMachine)
    {
    }

    void Replenish(unsigned count) override
    {
        std::cout << "Wait for giving a gumball\n";
    }

    void InsertQuarter() override
    {
        if (m_gumballMachine.GetQuartersCount() < m_gumballMachine.GetMaxQuartersCount())
        {
            std::cout << "You inserted a quarter\n";
            m_gumballMachine.InsertQuarter();
            m_gumballMachine.SetHasQuarterState();
        }
        else
        {
            std::cout << "You can't insert more quarter than " << m_gumballMachine.GetMaxQuartersCount() << std::endl;
        }
    }

    void EjectQuarter() override
    {
        std::cout << "Sorry you already turned the crank\n";
    }

    void TurnCrank() override
    {
        std::cout << "Turning twice doesn't get you another gumball\n";
    }

    void Dispense() override
    {
        m_gumballMachine.ReleaseBall();
        std::cout << "A gumball comes rolling out the slot...\n"; // Добавляем вывод

        if (m_gumballMachine.GetBallCount() == 0)
        {
            std::cout << "Oops, out of gumballs\n";
            m_gumballMachine.SetSoldOutState();
        }
        else
        {
            if (m_gumballMachine.GetQuartersCount() == 0)
            {
                m_gumballMachine.SetNoQuarterState();
            }
            else
            {
                m_gumballMachine.SetHasQuarterState(); // Остались монеты - остаемся в has quarter
            }
        }
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "delivering a gumball";
    }

private:
    IMultiGumballMachine& m_gumballMachine;
};
