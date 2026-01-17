#pragma once
#include <vector>

#include "../Command/ICommand.h"

class History
{
public:
    void AddCommand(const ICommandPtr& command)
    {
        CleanupOldestCommandIfNeeded();
        m_executeCommands.push_back(command);
        m_unexecuteCommands.clear();
    }

    [[nodiscard]] bool CanUndo() const
    {
        return !m_executeCommands.empty();
    }

    [[nodiscard]] bool CanRedo() const
    {
        return !m_unexecuteCommands.empty();
    }

    void Undo()
    {
        if (!CanUndo())
        {
            return;
        }

        auto command = std::move(m_executeCommands.back());
        m_executeCommands.pop_back();
        command->Unexecute();
        m_unexecuteCommands.push_back(std::move(command));
    }

    void Redo()
    {
        if (!CanRedo())
        {
            return;
        }

        auto command = std::move(m_unexecuteCommands.back());
        m_unexecuteCommands.pop_back();
        command->Execute();
        m_executeCommands.push_back(std::move(command));
    }


private:
    static constexpr size_t MAX_HISTORY_SIZE = 10;

    std::deque<ICommandPtr> m_executeCommands;
    std::vector<ICommandPtr> m_unexecuteCommands;

    void CleanupOldestCommandIfNeeded()
    {
        if (m_executeCommands.size() < MAX_HISTORY_SIZE)
        {
            return;
        }

        if (!m_executeCommands.empty())
        {
            m_executeCommands.pop_front();
        }
    }
};
