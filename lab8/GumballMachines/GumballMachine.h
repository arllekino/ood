#pragma once
#include <iostream>

#include "../States/HasQuarterState.h"
#include "../States/NoQuarterState.h"
#include "../States/SoldOutState.h"
#include "../States/SoldState.h"
#include "../States/IState/IState.h"
#include "IGumballMachine/IGumballMachine.h"

class GumballMachine : private IGumballMachine
{
public:
    GumballMachine(unsigned numBalls)
        : m_count(numBalls)
    {
        if (m_count > 0)
        {
            SetNoQuarterState();
        }
        else
        {
            SetSoldOutState();
        }
    }
    void EjectQuarter()
    {
        m_currentState->EjectQuarter();
    }
    void InsertQuarter()
    {
        m_currentState->InsertQuarter();
    }
    void TurnCrank()
    {
        m_currentState->TurnCrank();
        m_currentState->Dispense();
    }
    [[nodiscard]] std::string ToString() const
    {
        return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2025
Inventory: {} gumball{}
Machine is {}
)",
            m_count,
            m_count != 1 ? "s" : "",
            m_currentState->ToString()
        );
    }

private:
    [[nodiscard]] unsigned GetBallCount() const override
    {
        return m_count;
    }
    void ReleaseBall() override
    {
        if (m_count != 0)
        {
            std::cout << "A gumball comes rolling out the slot...\n";
            --m_count;
        }
    }
    void SetSoldOutState() override
    {
        m_currentState.reset(new SoldOutState(*this));
    }
    void SetNoQuarterState() override
    {
        m_currentState.reset(new NoQuarterState(*this));
    }
    void SetSoldState() override
    {
        m_currentState.reset(new SoldState(*this));
    }
    void SetHasQuarterState() override
    {
        m_currentState.reset(new HasQuarterState(*this));
    }

private:
    unsigned m_count = 0;
    std::unique_ptr<IState> m_currentState;
};