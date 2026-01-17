#pragma once
#include <memory>
#include <__format/format_functions.h>

#include "../States/IState/IState.h"
#include "../States/MultiMachineStates/SoldState.h"
#include "../States/MultiMachineStates/HasQuartersState.h"
#include "../States/MultiMachineStates/NoQuartersState.h"
#include "../States/MultiMachineStates/SoldOutState.h"

class MultiGumballMachine : private IMultiGumballMachine
{
public:
    explicit MultiGumballMachine(unsigned gumballsCount, unsigned maxQuartersCount = 5)
            : m_gumballsCount(gumballsCount),
            m_maxQuartersCount(maxQuartersCount),
            m_quartersCount(0)
    {
        if (m_gumballsCount > 0)
        {
            SetNoQuarterState();
        }
        else
        {
            SetSoldOutState();
        }
    }

    void AddGumball(unsigned count)
    {
        m_currentState->Replenish(count);
    }

    void AddQuarter()
    {
        m_currentState->InsertQuarter();
    }

    void GetBackQuarter()
    {
        m_currentState->EjectQuarter();
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
Inventory:
 - {} gumball{}
 - {} quarter{}
Machine is {}
)",
            m_gumballsCount,
            m_gumballsCount != 1 ? "s" : "",
            m_quartersCount,
            m_quartersCount != 1 ? "s" : "",
            m_currentState->ToString()
        );
    }

private:
    std::unique_ptr<IReplenishableState> m_currentState;
    unsigned m_gumballsCount;
    unsigned m_maxQuartersCount;
    unsigned m_quartersCount;

    void Replenish(unsigned count) override
    {
        m_gumballsCount += count;
    }

    void ReleaseBall() override
    {
        if (m_gumballsCount > 0)
        {
            m_gumballsCount--;
            m_quartersCount--;
        }
    }

    unsigned GetBallCount() const override
    {
        return m_gumballsCount;
    }

    unsigned GetQuartersCount() const override
    {
        return m_quartersCount;
    }

    unsigned GetMaxQuartersCount() const override
    {
        return m_maxQuartersCount;
    }

    void InsertQuarter() override
    {
        ++m_quartersCount;
    }

    void EjectQuarter() override
    {
        --m_quartersCount;
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
};
