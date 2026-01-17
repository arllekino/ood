#include <catch2/catch_all.hpp>
#include <sstream>

#include "../GumballMachines/MultiGumballMachine.h"
#include "../GumballMachines/NaiveMultiGumballMachine.h"
#include "../States/MultiMachineStates/HasQuartersState.h"
#include "../States/MultiMachineStates/NoQuartersState.h"
#include "../States/MultiMachineStates/SoldOutState.h"
#include "../States/MultiMachineStates/SoldState.h"

static const std::string HAS_QUARTERS_MESSAGE = "waiting for turn of crank";
static const std::string SOLD_MESSAGE = "delivering a gumball";
static const std::string NO_QUARTERS_MESSAGE = "waiting for quarter";
static const std::string SOLD_OUT_MESSAGE = "sold out";

static std::string GetMockMultiGumballMachineAsString(unsigned balls, unsigned quarters, const std::string& stateMessage)
{
    return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2025
Inventory:
 - {} gumball{}
 - {} quarter{}
Machine is {}
)",
        balls,
        balls != 1 ? "s" : "",
        quarters,
        quarters != 1 ? "s" : "",
        stateMessage
    );
}

TEST_CASE("MultiGumballMachine - Replenish in NoQuarterState")
{
    SECTION("Replenish empty machine")
    {
        MultiGumballMachine machine(0, 5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 0, SOLD_OUT_MESSAGE));
        
        machine.AddGumball(3);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Replenish machine with existing balls")
    {
        MultiGumballMachine machine(2, 5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 0, NO_QUARTERS_MESSAGE));
        
        machine.AddGumball(3);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(5, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Replenish preserves quarters count")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 2, HAS_QUARTERS_MESSAGE));
        
        machine.AddGumball(3);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(5, 2, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Replenish multiple times")
    {
        MultiGumballMachine machine(1, 5);
        machine.AddGumball(2);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 0, NO_QUARTERS_MESSAGE));
        
        machine.AddGumball(1);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(4, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("MultiGumballMachine - Replenish in HasQuarterState")
{
    SECTION("Replenish with quarters inserted")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 2, HAS_QUARTERS_MESSAGE));
        
        machine.AddGumball(3);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(5, 2, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Replenish when machine was almost empty")
    {
        MultiGumballMachine machine(1, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        machine.AddQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(1, 3, HAS_QUARTERS_MESSAGE));
        
        machine.AddGumball(4);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(5, 3, HAS_QUARTERS_MESSAGE));
    }
}

TEST_CASE("MultiGumballMachine - Replenish in SoldOutState")
{
    SECTION("Replenish completely empty machine")
    {
        MultiGumballMachine machine(0, 5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 0, SOLD_OUT_MESSAGE));
        
        machine.AddGumball(5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(5, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Replenish sold out machine with quarters")
    {
        MultiGumballMachine machine(1, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 1, SOLD_OUT_MESSAGE));
        
        machine.AddGumball(3);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 1, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Replenish sold out machine without quarters")
    {
        MultiGumballMachine machine(0, 5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 0, SOLD_OUT_MESSAGE));
        
        machine.AddGumball(2);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("MultiGumballMachine - Replenish edge cases")
{
    SECTION("Replenish zero balls")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddGumball(0);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Replenish large amount")
    {
        MultiGumballMachine machine(1, 5);
        machine.AddGumball(100);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(101, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("States Replenish Behavior")
{
    SECTION("NoQuarterState replenish")
    {
        MultiGumballMachine machine(2, 5);
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.Replenish(3);

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.empty());
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(5, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("HasQuarterState replenish")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.Replenish(3);

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.empty());
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(5, 2, HAS_QUARTERS_MESSAGE));
    }

    SECTION("SoldOutState replenish")
    {
        MultiGumballMachine machine(0, 5);
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldOutState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.Replenish(3);

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.empty());
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("SoldState replenish - should show message")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddQuarter();
        machine.TurnCrank();
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.Replenish(3);

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "Wait for giving a gumball\n");
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(1, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("Replenish Integration Scenarios")
{
    SECTION("Complex scenario: replenish during usage")
    {
        MultiGumballMachine machine(2, 5);
        
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 0, NO_QUARTERS_MESSAGE));
        
        machine.AddQuarter();
        machine.AddQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 2, HAS_QUARTERS_MESSAGE));
        
        machine.AddGumball(2);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(4, 2, HAS_QUARTERS_MESSAGE));
        
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 1, HAS_QUARTERS_MESSAGE));
        
        machine.AddGumball(1);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(4, 1, HAS_QUARTERS_MESSAGE));
        
        machine.TurnCrank();
        machine.TurnCrank();
        machine.TurnCrank();
        
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Replenish to prevent sold out")
    {
        MultiGumballMachine machine(1, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 1, SOLD_OUT_MESSAGE));
        
        machine.AddGumball(2);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
        
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(1, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("Replenish State Transitions")
{
    SECTION("SoldOut to NoQuarter after replenish")
    {
        MultiGumballMachine machine(0, 5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 0, SOLD_OUT_MESSAGE));
        
        machine.AddGumball(1);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(1, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("SoldOut to HasQuarter after replenish with existing quarters")
    {
        MultiGumballMachine machine(1, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 1, SOLD_OUT_MESSAGE));
        
        machine.AddGumball(2);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
    }
}