#pragma once
#include <assert.h>
#include <iostream>
#include <string>
#include <__format/format_functions.h>

#include "IGumballMachine/IMultiGumballMachine.h"

enum class MultiState
{
    HAS_QUARTERS_STATE,
    NO_QUARTERS_STATE,
    SOLD_OUT_STATE,
    SOLD_STATE
};

class NaiveMultiGumballMachine : private IMultiGumballMachine
{
public:
    explicit NaiveMultiGumballMachine(unsigned gumballsCount, unsigned maxQuartersCount = 5)
        : m_state(gumballsCount > 0
            ? MultiState::NO_QUARTERS_STATE
            : MultiState::SOLD_OUT_STATE),
        m_gumballsCount(gumballsCount),
        m_maxQuartersCount(maxQuartersCount),
        m_quartersCount(0)
    {
    }

    void AddGumball(unsigned count)
    {
        Replenish(count);
    }

    void AddQuarter()
    {
        InsertQuarter();
    }

    void GetBackQuarter()
    {
        EjectQuarter();
    }

    void TurnCrank()
    {
        switch (m_state)
        {
            case MultiState::NO_QUARTERS_STATE:
                std::cout << "You turned but there's no quarter\n";
                break;
            case MultiState::SOLD_OUT_STATE:
                std::cout << "You turned but there's no gumballs\n";
                break;
            case MultiState::SOLD_STATE:
                break;
            case MultiState::HAS_QUARTERS_STATE:
                SetSoldState();
                Dispense();
                break;
        }
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
            GetStateASString()
        );
    }

private:
    MultiState m_state;
    unsigned m_gumballsCount;
    unsigned m_maxQuartersCount;
    unsigned m_quartersCount;

    void Replenish(unsigned count) override
    {
        m_gumballsCount += count;
    }

    void ReleaseBall() override
    {
        m_gumballsCount--;
        m_quartersCount--;
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
        switch (m_state)
        {
            case MultiState::NO_QUARTERS_STATE:
                SetHasQuarterState();
            m_quartersCount++;
            std::cout << "You inserted a quarter\n";
            break;
            case MultiState::SOLD_OUT_STATE:
                std::cout << "You can't insert a quarter, the machine is sold out\n";
            break;
            case MultiState::SOLD_STATE:
            case MultiState::HAS_QUARTERS_STATE:
                TryToInsertQuarter();
            break;
        }
    }

    void EjectQuarter() override
    {
        switch (m_state)
        {
            case MultiState::NO_QUARTERS_STATE:
                std::cout << "You haven't inserted a quarter\n";
            break;
            case MultiState::SOLD_OUT_STATE:
            case MultiState::SOLD_STATE:
            case MultiState::HAS_QUARTERS_STATE:
                TryToEjectQuarter();
            break;
        }
    }

    void SetSoldOutState() override
    {
        m_state = MultiState::SOLD_OUT_STATE;
    }

    void SetNoQuarterState() override
    {
        m_state = MultiState::NO_QUARTERS_STATE;
    }

    void SetSoldState() override
    {
        m_state = MultiState::SOLD_STATE;
    }

    void SetHasQuarterState() override
    {
        m_state = MultiState::HAS_QUARTERS_STATE;
    }

    void Dispense()
    {
        ReleaseBall();
        if (GetBallCount() == 0)
        {
            std::cout << "Oops, out of gumballs\n";
            SetSoldOutState();
        }
        else
        {
            if (GetQuartersCount() == 0)
            {
                SetNoQuarterState();
            }
            else
            {
                SetHasQuarterState();
            }
        }
    }

    void TryToInsertQuarter()
    {
        if (m_quartersCount < m_maxQuartersCount)
        {
            m_quartersCount++;
            std::cout << "You inserted a quarter\n";
        }
        else
        {
            std::cout << "You can't insert a quarter, the machine is full of quarters\n";
        }
    }

    void TryToEjectQuarter()
    {
        if (m_quartersCount != 0)
        {
            m_quartersCount--;
            std::cout << "Quarter returned\n";
            if (m_quartersCount == 0)
            {
                SetNoQuarterState();
            }
        }
        else
        {
            std::cout << "You haven't inserted a quarter\n";
        }
    }

    std::string GetStateASString() const
    {
        switch (m_state)
        {
            case MultiState::NO_QUARTERS_STATE:
                return "waiting for quarter";
            case MultiState::SOLD_OUT_STATE:
                return "sold out";
            case MultiState::SOLD_STATE:
                return "delivering a gumball";
            case MultiState::HAS_QUARTERS_STATE:
                return "waiting for turn of crank";
        }
        assert(false);
    }
};
