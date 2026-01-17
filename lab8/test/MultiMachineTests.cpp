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

TEST_CASE("MultiGumballMachine - Constructor")
{
    SECTION("Constructor with balls > 0")
    {
        MultiGumballMachine machine(3, 5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Constructor with 0 balls")
    {
        MultiGumballMachine machine(0, 5);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 0, SOLD_OUT_MESSAGE));
    }
}

TEST_CASE("MultiGumballMachine - Insert Quarter")
{
    SECTION("Insert quarter in machine with balls")
    {
        MultiGumballMachine machine(2, 5);
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.AddQuarter();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output == "You inserted a quarter\n");
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Insert multiple quarters up to max")
    {
        MultiGumballMachine machine(2, 3);
        
        machine.AddQuarter();
        machine.AddQuarter();
        machine.AddQuarter();
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.AddQuarter();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output.find("You can't insert more quarter than 3") != std::string::npos);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 3, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Insert quarter in sold out machine")
    {
        MultiGumballMachine machine(0, 5);
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.AddQuarter();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output == "You can't insert a quarter, the machine is sold out\n");
    }
}

TEST_CASE("MultiGumballMachine - Eject Quarter")
{
    SECTION("Eject multiple quarters one by one")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        machine.AddQuarter();

        machine.GetBackQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 2, HAS_QUARTERS_MESSAGE));

        machine.GetBackQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));

        machine.GetBackQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("MultiGumballMachine - Turn Crank")
{
    SECTION("Turn crank with quarter and multiple balls")
    {
        MultiGumballMachine machine(3, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.TurnCrank();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output.find("You turned...") != std::string::npos);
        REQUIRE(output.find("A gumball comes rolling out the slot...") != std::string::npos);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Turn crank until sold out with extra quarters")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        machine.AddQuarter();

        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(1, 2, HAS_QUARTERS_MESSAGE));
        
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 1, SOLD_OUT_MESSAGE));
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.GetBackQuarter();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output == "Quarter returned\n");
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 0, SOLD_OUT_MESSAGE));
    }
}

TEST_CASE("HasQuartersState")
{
    MultiGumballMachine machine(3, 3);
    machine.AddQuarter();
    
    SECTION("Insert quarter when not full")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You inserted a quarter\n");
    }

    SECTION("Insert quarter when full")
    {
        machine.AddQuarter();
        machine.AddQuarter();
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.find("You can't insert more quarter than 3") != std::string::npos);
    }

    SECTION("Eject quarter")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.EjectQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "Quarter returned\n");
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(3, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Turn crank")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.TurnCrank();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You turned...\n");
    }

    SECTION("ToString")
    {
        HasQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        REQUIRE(state.ToString() == "waiting for turn of crank");
    }
}

TEST_CASE("NoQuartersState")
{
    MultiGumballMachine machine(2, 3);

    SECTION("Insert quarter")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You inserted a quarter\n");
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Eject quarter without insertion")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.EjectQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You haven't inserted a quarter\n");
    }

    SECTION("Turn crank without quarter")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.TurnCrank();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You turned but there's no quarter\n");
    }

    SECTION("ToString")
    {
        NoQuarterState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        REQUIRE(state.ToString() == "waiting for quarter");
    }
}

TEST_CASE("SoldState")
{
    SECTION("Dispense with remaining balls")
    {
        MultiGumballMachine machine(2, 5);
        machine.AddQuarter();

        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.Dispense();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.find("A gumball comes rolling out the slot...") != std::string::npos);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(1, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("SoldOutState")
{
    MultiGumballMachine machine(0, 3);

    SECTION("Insert quarter in sold out")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldOutState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You can't insert a quarter, the machine is sold out\n");
    }

    SECTION("Eject quarter from sold out with quarters")
    {
        MultiGumballMachine machineWithQuarters(1, 3);
        machineWithQuarters.AddQuarter();
        machineWithQuarters.AddQuarter();
        machineWithQuarters.TurnCrank();
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldOutState state(reinterpret_cast<IMultiGumballMachine&>(machineWithQuarters));
        state.EjectQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "Quarter returned\n");
    }

    SECTION("ToString")
    {
        SoldOutState state(reinterpret_cast<IMultiGumballMachine&>(machine));
        REQUIRE(state.ToString() == "sold out");
    }
}

TEST_CASE("NaiveMultiGumballMachine - Basic Operations")
{
    SECTION("Constructor and initial state")
    {
        NaiveMultiGumballMachine machine(2, 3);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 0, NO_QUARTERS_MESSAGE));
    }

    SECTION("Insert quarters up to max")
    {
        NaiveMultiGumballMachine machine(2, 2);
        
        machine.AddQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
        
        machine.AddQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 2, HAS_QUARTERS_MESSAGE));
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.AddQuarter();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output.find("You can't insert a quarter, the machine is full of quarters") != std::string::npos);
    }

    SECTION("Turn crank with quarters")
    {
        NaiveMultiGumballMachine machine(3, 3);
        machine.AddQuarter();
        machine.AddQuarter();
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.TurnCrank();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output.find("Oops, out of gumballs") == std::string::npos);
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Eject quarters one by one")
    {
        NaiveMultiGumballMachine machine(2, 3);
        machine.AddQuarter();
        machine.AddQuarter();
        
        machine.GetBackQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 1, HAS_QUARTERS_MESSAGE));
        
        machine.GetBackQuarter();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(2, 0, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("NaiveMultiGumballMachine - Edge Cases")
{
    SECTION("Exhaust balls with extra quarters")
    {
        NaiveMultiGumballMachine machine(2, 5);
        machine.AddQuarter();
        machine.AddQuarter();
        machine.AddQuarter();
        
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(1, 2, HAS_QUARTERS_MESSAGE));
        
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockMultiGumballMachineAsString(0, 1, SOLD_OUT_MESSAGE));
    }

    SECTION("Operations on sold out machine")
    {
        NaiveMultiGumballMachine machine(0, 3);
        
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());
        
        machine.AddQuarter();
        
        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);
        
        REQUIRE(output == "You can't insert a quarter, the machine is sold out\n");
    }
}