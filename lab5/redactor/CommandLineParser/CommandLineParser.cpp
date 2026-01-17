//
// Created by Miroslav Aktuganov on 23.10.2025.
//

#include "CommandLineParser.h"

#include <iostream>
#include <sstream>

std::pair<ActionType, CommandLineParameters> CommandLineParser::Parse(std::istringstream& iss)
{
    std::string keyword;
    iss >> keyword;
    const auto actionType = DefineActionTypeByKeyWord(keyword);
    const auto parameters = DefineCommandLineParameters(actionType, iss);
    return {actionType, parameters};
}

ActionType CommandLineParser::DefineActionTypeByKeyWord(const std::string& keyword)
{
    if (keyword == "InsertParagraph")
    {
        return ActionType::INSERT_PARAGRAPH;
    }
    if (keyword == "InsertImage")
    {
        return ActionType::INSERT_IMAGE;
    }
    if (keyword == "SetTitle")
    {
        return ActionType::SET_TITLE;
    }
    if (keyword == "List")
    {
        return ActionType::LIST;
    }
    if (keyword == "ReplaceText")
    {
        return ActionType::REPLACE_TEXT;
    }
    if (keyword == "ResizeImage")
    {
        return ActionType::RESIZE_IMAGE;
    }
    if (keyword == "DeleteItem")
    {
        return ActionType::DELETE_ITEM;
    }
    if (keyword == "Help")
    {
        return ActionType::HELP;
    }
    if (keyword == "Undo")
    {
        return ActionType::UNDO;
    }
    if (keyword == "Redo")
    {
        return ActionType::REDO;
    }
    if (keyword == "Save")
    {
        return ActionType::SAVE;
    }
    throw std::invalid_argument("Unrecognized keyword");
}

CommandLineParameters CommandLineParser::DefineCommandLineParameters(
    const ActionType actionType,
    std::istringstream &iss)
{
    switch (actionType)
    {
        case ActionType::INSERT_PARAGRAPH:
            return CommandLineParameters{ParseParamsForInsertingParagraph(iss)};
        case ActionType::INSERT_IMAGE:
            return CommandLineParameters{ParseParamsForInsertingImageParameters(iss)};
        case ActionType::SET_TITLE:
            return CommandLineParameters{ParseTitle(iss)};
        case ActionType::REPLACE_TEXT:
            return CommandLineParameters{ParseReplaceTextParameters(iss)};
        case ActionType::RESIZE_IMAGE:
            return CommandLineParameters{ParseImageParameters(iss)};
        case ActionType::DELETE_ITEM:
            return CommandLineParameters{ParsePosition(iss)};
        case ActionType::SAVE:
            return CommandLineParameters{ParseSaveDocumentPath(iss)};
        case ActionType::LIST:
        case ActionType::HELP:
        case ActionType::UNDO:
        case ActionType::REDO:
            return CommandLineParameters{std::monostate{}};
        default:
            throw std::invalid_argument("Unrecognized action type");
    }
}

InsertParagraphParameters CommandLineParser::ParseParamsForInsertingParagraph(std::istringstream &iss)
{
    std::string strPosition, text;
    iss >> strPosition;

    const size_t posEnd = strPosition.find(POSITION_END_IN_LINE);
    std::optional<size_t> position = std::nullopt;
    if (posEnd != std::string::npos)
    {
        position = static_cast<size_t>(std::stoi(strPosition.substr(0, posEnd)));
        std::getline(iss, text);
    }
    else
    {
        std::getline(iss, text);
    }

    if (!text.empty() && text[0] == ' ')
    {
        text.erase(0, 1);
    }

    return {
        position,
        text
    };
}

InsertImageParameters CommandLineParser::ParseParamsForInsertingImageParameters(std::istringstream& iss)
{
    std::string strPosition, strWidth, strHeight, path;
    iss >> strPosition >> strWidth >> strHeight >> path;

    const size_t posEnd = strPosition.find(POSITION_END_IN_LINE);
    std::optional<size_t> position = std::nullopt;
    if (posEnd != std::string::npos)
    {
        position = static_cast<size_t>(std::stoi(strPosition.substr(0, posEnd)));
    }

    return {
        position,
        static_cast<unsigned>(std::stoi(strWidth)),
        static_cast<unsigned>(std::stoi(strHeight)),
        path
    };
}

DocumentTitle CommandLineParser::ParseTitle(std::istringstream &iss)
{
    std::string title;
    std::getline(iss, title);

    if (!title.empty() && title[0] == ' ')
    {
        title.erase(0, 1);
    }

    return {title};
}

ReplaceTextParameters CommandLineParser::ParseReplaceTextParameters(std::istringstream &iss)
{
    std::string strPosition, text;
    iss >> strPosition;
    std::getline(iss, text);

    if (!text.empty() && text[0] == ' ')
    {
        text.erase(0, 1);
    }

    return {
        static_cast<size_t>(std::stoi(strPosition)) - 1,
        text,
    };
}

ResizeImageParameters CommandLineParser::ParseImageParameters(std::istringstream& iss)
{
    std::string strPosition, strWidth, strHeight;
    iss >> strPosition >> strWidth >> strHeight;
    return {
        static_cast<size_t>(std::stoi(strPosition)) - 1,
        static_cast<unsigned>(std::stoi(strWidth)),
        static_cast<unsigned>(std::stoi(strHeight))
    };
}

Position CommandLineParser::ParsePosition(std::istringstream& iss)
{
    std::string strPosition;
    iss >> strPosition;
    return static_cast<Position>(std::stoi(strPosition)) - 1;
}

SaveDocumentPath CommandLineParser::ParseSaveDocumentPath(std::istringstream& iss)
{
    std::string path;
    iss >> path;
    return path;
}