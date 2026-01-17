#pragma once

#include <iostream>
#include <unordered_set>

#include "../Action/ActionType.h"
#include "../Command/DeleteItemCommand.h"
#include "../Command/ICommand.h"
#include "../Command/InsertImageCommand.h"
#include "../Command/InsertParagraphCommand.h"
#include "../Command/ReplaceTextCommand.h"
#include "../Command/ResizeImageCommand.h"
#include "../Command/SetTitleCommand.h"
#include "../CommandLineParser/CommandLineParser.h"
#include "../Document/IDocument.h"
#include "../History/History.h"

class DocumentController
{
public:
    explicit DocumentController(IDocumentPtr document)
        : m_document(std::move(document)),
        m_history(History())
    {
    }

    void ExecuteCommand(const std::pair<ActionType, CommandLineParameters>& command)
    {
        if (IsUndoRedoAction(command.first))
        {
            const auto commandImpl = CreateCommandImpl(command);
            commandImpl->Execute();

            m_history.AddCommand(commandImpl);
        }
        else
        {
            ExecuteSimpleCommand(command);
        }
    }

private:
    static constexpr size_t MAX_HISTORY_SIZE = 10;

    IDocumentPtr m_document;
    History m_history;

    static bool IsUndoRedoAction(const ActionType actionType)
    {
        static const std::unordered_set<ActionType> undoRedoActions = {
            ActionType::INSERT_PARAGRAPH,
            ActionType::INSERT_IMAGE,
            ActionType::SET_TITLE,
            ActionType::REPLACE_TEXT,
            ActionType::RESIZE_IMAGE,
            ActionType::DELETE_ITEM
        };
        return undoRedoActions.contains(actionType);
    }

    void ExecuteSimpleCommand(const std::pair<ActionType, CommandLineParameters>& command)
    {
        switch (command.first)
        {
            case ActionType::LIST:
                DocumentList();
                break;
            case ActionType::HELP:
                PrintHelp();
                break;
            case ActionType::UNDO:
                OnUndo();
                break;
            case ActionType::REDO:
                OnRedo();
                break;
            case ActionType::SAVE:
                SaveDocument(std::get<SaveDocumentPath>(command.second));
                break;
            default:
                throw std::invalid_argument("Invalid action type");
        }
    }

    void SaveDocument(const SaveDocumentPath& path) const
    {
        try
        {
            m_document->Save(path);
            std::cout << "Document saved successfully to: " << path << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error saving document: " << e.what() << std::endl;
        }
    }

    void DocumentList() const
    {
        std::cout << "Title: " << m_document->GetTitle().title << std::endl;

        const auto itemsCount = m_document->GetItemsCount();
        for (size_t i = 0; i < itemsCount; ++i)
        {
            auto item = m_document->GetItem(i);
            if (const auto image = item.GetImage(); image != nullptr)
            {
                PrintImageInfo(i + 1, image);
            }
            else if (const auto paragraph = item.GetParagraph(); paragraph != nullptr)
            {
                PrintParagraphInfo(i + 1, paragraph);
            }
        }
    }

    void OnUndo()
    {
        if (!m_history.CanUndo())
        {
            std::cout << "Cannot undo - no commands in history" << std::endl;
            return;
        }
        m_history.Undo();
    }

    void OnRedo()
    {
        if (!m_history.CanRedo())
        {
            std::cout << "Cannot redo - no commands to redo" << std::endl;
            return;
        }
        m_history.Redo();
    }

    static void PrintImageInfo(const size_t pos, const IImagePtr& image)
    {
        std::cout
            << pos << ". "
            << "Image: "
            << image->GetWidth() << " "
            << image->GetHeight() << " "
            << image->GetPath() << std::endl;
    }

    static void PrintParagraphInfo(const size_t pos, const IParagraphPtr& paragraph)
    {
        std::cout
            << pos << ". "
            << "Paragraph: "
            << paragraph->GetText() << std::endl;
    }

    static void PrintHelp()
    {
        std::cout << "Available commands:\n"
                  << "InsertParagraph <pos>|end <text> - Insert paragraph at position\n"
                  << "InsertImage <pos>|end <width> <height> <path> - Insert image\n"
                  << "SetTitle <title> - Set document title\n"
                  << "List - Show document contents\n"
                  << "ReplaceText <pos> <text> - Replace paragraph text\n"
                  << "ResizeImage <pos> <width> <height> - Resize image\n"
                  << "DeleteItem <pos> - Delete item at position\n"
                  << "Undo - Undo last command\n"
                  << "Redo - Redo last undone command\n"
                  << "Save <path> - Save document to HTML\n"
                  << "Help - Show this help\n";
    }

    ICommandPtr CreateCommandImpl(const std::pair<ActionType, CommandLineParameters>& command)
    {
        return std::visit([&]<typename T0>(T0&& arg) -> ICommandPtr {
            using T = std::decay_t<T0>;

            if constexpr (std::is_same_v<T, InsertParagraphParameters>)
            {
                return std::make_unique<InsertParagraphCommand>(m_document, arg);
            }
            else if constexpr (std::is_same_v<T, InsertImageParameters>)
            {
                return std::make_unique<InsertImageCommand>(m_document, arg);
            }
            else if constexpr (std::is_same_v<T, DocumentTitle>)
            {
                return std::make_unique<SetTitleCommand>(m_document, arg);
            }
            else if constexpr (std::is_same_v<T, ReplaceTextParameters>)
            {
                return std::make_unique<ReplaceTextCommand>(m_document, arg);
            }
            else if constexpr (std::is_same_v<T, ResizeImageParameters>)
            {
                return std::make_unique<ResizeImageCommand>(m_document, arg);
            }
            else if constexpr (std::is_same_v<T, Position>)
            {
                return std::make_unique<DeleteItemCommand>(m_document, arg);
            }
            else
            {
                throw std::invalid_argument("Unsupported parameters type");
            }
        }, command.second);
    }
};

// class History for undoREdo
// History хранит команды
// вся логика undoredo в history
