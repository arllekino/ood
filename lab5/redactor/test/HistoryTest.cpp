#include <catch2/catch_test_macros.hpp>
#include "../History/History.h"

class MockCommand : public ICommand
{
public:
    void Execute() override 
    {
        executeCount++;
        currentValue = newValue;
    }

    void Unexecute() override 
    {
        unexecuteCount++;
        currentValue = oldValue;
    }

    [[nodiscard]] int GetExecuteCount() const { return executeCount; }
    [[nodiscard]] int GetUnexecuteCount() const { return unexecuteCount; }
    [[nodiscard]] int GetCurrentValue() const { return currentValue; }

    void SetValues(const int oldVal, const int newVal)
    {
        oldValue = oldVal;
        newValue = newVal;
        currentValue = oldVal;
    }

private:
    int executeCount = 0;
    int unexecuteCount = 0;
    int oldValue = 0;
    int newValue = 0;
    int currentValue = 0;
};

TEST_CASE("History commands")
{
    History history;

    SECTION("New history cannot undo/redo")
    {
        REQUIRE_FALSE(history.CanUndo());
        REQUIRE_FALSE(history.CanRedo());
    }

    SECTION("Add command enables undo")
    {
        auto command = std::make_shared<MockCommand>();
        history.AddCommand(command);

        REQUIRE(history.CanUndo());
        REQUIRE_FALSE(history.CanRedo());
    }

    SECTION("Undo and redo single command")
    {
        auto command = std::make_shared<MockCommand>();
        command->SetValues(10, 20);
        
        command->Execute();
        history.AddCommand(command);

        REQUIRE(command->GetExecuteCount() == 1);
        REQUIRE(command->GetUnexecuteCount() == 0);

        history.Undo();
        REQUIRE(command->GetUnexecuteCount() == 1);
        REQUIRE(history.CanRedo());
        REQUIRE_FALSE(history.CanUndo());

        history.Redo();
        REQUIRE(command->GetExecuteCount() == 2);
        REQUIRE(history.CanUndo());
        REQUIRE_FALSE(history.CanRedo());
    }

    SECTION("Undo and redo multiple commands")
    {
        auto command1 = std::make_shared<MockCommand>();
        auto command2 = std::make_shared<MockCommand>();
        
        command1->SetValues(1, 2);
        command2->SetValues(2, 3);

        command1->Execute();
        history.AddCommand(command1);
        
        command2->Execute();
        history.AddCommand(command2);

        REQUIRE(history.CanUndo());
        REQUIRE_FALSE(history.CanRedo());

        history.Undo();
        REQUIRE(command2->GetUnexecuteCount() == 1);
        REQUIRE(history.CanUndo());
        REQUIRE(history.CanRedo());

        history.Undo();
        REQUIRE(command1->GetUnexecuteCount() == 1);
        REQUIRE_FALSE(history.CanUndo());
        REQUIRE(history.CanRedo());

        history.Redo();
        REQUIRE(command1->GetExecuteCount() == 2);
        REQUIRE(history.CanUndo());
        REQUIRE(history.CanRedo());

        history.Redo();
        REQUIRE(command2->GetExecuteCount() == 2);
        REQUIRE(history.CanUndo());
        REQUIRE_FALSE(history.CanRedo());
    }

    SECTION("Adding command clears redo stack")
    {
        auto command1 = std::make_shared<MockCommand>();
        auto command2 = std::make_shared<MockCommand>();
        auto command3 = std::make_shared<MockCommand>();
        
        command1->Execute();
        history.AddCommand(command1);
        
        command2->Execute();
        history.AddCommand(command2);

        history.Undo();
        history.Undo();
        
        REQUIRE(history.CanRedo());
        REQUIRE_FALSE(history.CanUndo());

        command3->Execute();
        history.AddCommand(command3);

        REQUIRE(history.CanUndo());
        REQUIRE_FALSE(history.CanRedo());
    }
}

TEST_CASE("History respects size limits")
{
    History history;

    SECTION("History grows up to limit")
    {
        for (int i = 0; i < 15; ++i)
        {
            auto command = std::make_shared<MockCommand>();
            command->Execute();
            history.AddCommand(command);
        }

        REQUIRE(history.CanUndo());
        
        for (int i = 0; i < 10; ++i)
        {
            history.Undo();
        }
        
        REQUIRE_FALSE(history.CanUndo());
        REQUIRE(history.CanRedo());
    }

    SECTION("Oldest commands are removed when exceeding limit")
    {
        std::vector<std::shared_ptr<MockCommand>> commands;
        
        for (int i = 0; i < 15; ++i)
        {
            auto command = std::make_shared<MockCommand>();
            command->SetValues(i, i + 1);
            command->Execute();
            commands.push_back(command);
            history.AddCommand(command);
        }

        for (int i = 0; i < 10; ++i)
        {
            history.Undo();
        }
        
        REQUIRE_FALSE(history.CanUndo());
        
        REQUIRE(commands[0]->GetUnexecuteCount() == 0);
        REQUIRE(commands[1]->GetUnexecuteCount() == 0);
        REQUIRE(commands[4]->GetUnexecuteCount() == 0);
        
        REQUIRE(commands[5]->GetUnexecuteCount() == 1);
        REQUIRE(commands[14]->GetUnexecuteCount() == 1);
    }
}

TEST_CASE("History handles edge cases")
{
    History history;

    SECTION("Undo on empty history does nothing")
    {
        REQUIRE_NOTHROW(history.Undo());
        REQUIRE_FALSE(history.CanUndo());
    }

    SECTION("Redo on empty history does nothing")
    {
        REQUIRE_NOTHROW(history.Redo());
        REQUIRE_FALSE(history.CanRedo());
    }

    SECTION("Commands are executed in correct order")
    {
        auto command1 = std::make_shared<MockCommand>();
        auto command2 = std::make_shared<MockCommand>();
        auto command3 = std::make_shared<MockCommand>();
        
        command1->SetValues(0, 1);
        command2->SetValues(1, 2);
        command3->SetValues(2, 3);

        command1->Execute();
        history.AddCommand(command1);
        
        command2->Execute();
        history.AddCommand(command2);
        
        command3->Execute();
        history.AddCommand(command3);

        history.Undo();
        REQUIRE(command3->GetUnexecuteCount() == 1);
        
        history.Undo();
        REQUIRE(command2->GetUnexecuteCount() == 1);
        
        history.Undo();
        REQUIRE(command1->GetUnexecuteCount() == 1);

        history.Redo();
        REQUIRE(command1->GetExecuteCount() == 2);
        
        history.Redo();
        REQUIRE(command2->GetExecuteCount() == 2);
        
        history.Redo();
        REQUIRE(command3->GetExecuteCount() == 2);
    }
}