//
// Created by Miroslav Aktuganov on 29.11.2025.
//

#include <catch2/catch_all.hpp>

#include "../GumballMachines/GumballMachine.h"

static const std::string HAS_QUARTERS_MESSAGE = "waiting for turn of crank";
static const std::string SOLD_MESSAGE = "delivering a gumball";
static const std::string NO_QUARTERS_MESSAGE = "waiting for quarter";
static const std::string SOLD_OUT_MESSAGE = "sold out";

static std::string GetMockGumballMachineAsString(unsigned count, const std::string& stateMessage)
{
    return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)",
            count,
            count != 1
                ? "s"
                : "",
            stateMessage
        );
}

TEST_CASE("Gumball Machine constuctor")
{
    SECTION("Constructor with quarters > 0")
    {
        GumballMachine machine(1);
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, NO_QUARTERS_MESSAGE));
    }

    SECTION("Constructor with 0 quarters")
    {
        GumballMachine machine(0);
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(0, SOLD_OUT_MESSAGE));
    }
}

TEST_CASE("Insert in cumball machine with balls")
{
    SECTION("Insert in machine with sold out state")
    {
        GumballMachine machine(0);
        machine.InsertQuarter();

        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(0, SOLD_OUT_MESSAGE));
    }

    SECTION("Insert in machine with balls")
    {
        GumballMachine machine(1);
        machine.InsertQuarter();

        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, HAS_QUARTERS_MESSAGE));
    }

    SECTION("Insert after turn crank in machine with 1 balls")
    {
        GumballMachine machine(1);
        machine.InsertQuarter();
        machine.TurnCrank();
        machine.InsertQuarter();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(0, SOLD_OUT_MESSAGE));
    }

    SECTION("Insert after turn crank in machine with 2 balls")
    {
        GumballMachine machine(2);
        machine.InsertQuarter();
        machine.TurnCrank();
        machine.InsertQuarter();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, HAS_QUARTERS_MESSAGE));
    }
}

TEST_CASE("Eject quarter in gumball machine")
{
    SECTION("Eject in empty machine")
    {
        GumballMachine machine(0);
        machine.EjectQuarter();

        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(0, SOLD_OUT_MESSAGE));
    }

    SECTION("Eject from machine with balls")
    {
        GumballMachine machine(1);
        machine.EjectQuarter();

        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, NO_QUARTERS_MESSAGE));
    }

    SECTION("Eject from machine with balls after inserting quarters")
    {
        GumballMachine machine(1);

        machine.InsertQuarter();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, HAS_QUARTERS_MESSAGE));
        machine.EjectQuarter();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, NO_QUARTERS_MESSAGE));
    }

    SECTION("Eject from machine with ball after turn crank")
    {
        GumballMachine machine(1);
        machine.InsertQuarter();
        machine.TurnCrank();
        machine.EjectQuarter();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(0, SOLD_OUT_MESSAGE));
    }

    SECTION("Eject from machine with balls after turn crank")
    {
        GumballMachine machine(2);
        machine.InsertQuarter();
        machine.TurnCrank();
        machine.EjectQuarter();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("Turn crank")
{
    SECTION("Empty machine")
    {
        GumballMachine machine(0);
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(0, SOLD_OUT_MESSAGE));
    }

    SECTION("With balls and without inserting quarter")
    {
        GumballMachine machine(1);
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, NO_QUARTERS_MESSAGE));
    }

    SECTION("machine with ball and with inserted quarter")
    {
        GumballMachine machine(1);
        machine.InsertQuarter();
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(0, SOLD_OUT_MESSAGE));
    }

    SECTION("machine with balls and with inserted quarter")
    {
        GumballMachine machine(2);
        machine.InsertQuarter();
        machine.TurnCrank();
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, NO_QUARTERS_MESSAGE));
    }
}

TEST_CASE("Has quarter State")
{
    GumballMachine machine(1);

    SECTION("Insert")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You can't insert another quarter\n");
    }

    SECTION("Eject")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.EjectQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "Quarter returned\n");
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, NO_QUARTERS_MESSAGE));
    }

    SECTION("Turn Crank")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.TurnCrank();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You turned...\n");
        REQUIRE(machine.ToString() == GetMockGumballMachineAsString(1, SOLD_MESSAGE));
    }

    SECTION("Dispense")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.Dispense();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "No gumball dispensed\n");
    }

    SECTION("To string")
    {
        HasQuarterState state(reinterpret_cast<IGumballMachine&>(machine));

        REQUIRE(state.ToString() == "waiting for turn of crank");
    }
}

TEST_CASE("Sold State")
{
    GumballMachine machine(1);

    SECTION("Insert")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldState state(reinterpret_cast<IGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "Please wait, we're already giving you a gumball\n");
    }

    SECTION("Eject")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldState state(reinterpret_cast<IGumballMachine&>(machine));
        state.EjectQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "Sorry you already turned the crank\n");
    }

    SECTION("Turn Crank")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldState state(reinterpret_cast<IGumballMachine&>(machine));
        state.TurnCrank();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "Turning twice doesn't get you another gumball\n");
    }

    SECTION("Dispense")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        HasQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.Dispense();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "No gumball dispensed\n");
    }

    SECTION("To string")
    {
        SoldState state(reinterpret_cast<IGumballMachine&>(machine));

        REQUIRE(state.ToString() == "delivering a gumball");
    }
}

TEST_CASE("No quarter State")
{
    GumballMachine machine(1);

    SECTION("Insert")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You inserted a quarter\n");
    }

    SECTION("Eject")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.EjectQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You haven't inserted a quarter\n");
    }

    SECTION("Turn Crank")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.TurnCrank();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You turned but there's no quarter\n");
    }

    SECTION("Dispense")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        NoQuarterState state(reinterpret_cast<IGumballMachine&>(machine));
        state.Dispense();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You need to pay first\n");
    }

    SECTION("To string")
    {
        NoQuarterState state(reinterpret_cast<IGumballMachine&>(machine));

        REQUIRE(state.ToString() == "waiting for quarter");
    }
}

TEST_CASE("Sold out State")
{
    GumballMachine machine(1);

    SECTION("Insert")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldOutState state(reinterpret_cast<IGumballMachine&>(machine));
        state.InsertQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You can't insert a quarter, the machine is sold out\n");
    }

    SECTION("Eject")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldOutState state(reinterpret_cast<IGumballMachine&>(machine));
        state.EjectQuarter();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You can't eject, you haven't inserted a quarter yet\n");
    }

    SECTION("Turn Crank")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldOutState state(reinterpret_cast<IGumballMachine&>(machine));
        state.TurnCrank();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "You turned but there's no gumballs\n");
    }

    SECTION("Dispense")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        SoldOutState state(reinterpret_cast<IGumballMachine&>(machine));
        state.Dispense();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "No gumball dispensed\n");
    }

    SECTION("To string")
    {
        SoldOutState state(reinterpret_cast<IGumballMachine&>(machine));

        REQUIRE(state.ToString() == "sold out");
    }
}