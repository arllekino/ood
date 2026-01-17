//
// Created by Miroslav Aktuganov on 23.10.2025.
//
#pragma once
#include <variant>

#include "../Action/ActionType.h"
#include "../CommandLineParameters/InsertImageParameters.h"
#include "../CommandLineParameters/InsertParagraphParameters.h"
#include "../CommandLineParameters/ReplaceTextParamaters.h"
#include "../CommandLineParameters/ResizeImageParameters.h"
#include "../CommandLineParameters/SetTitleParameters.h"
#include "../CommandLineParameters/Position.h"
#include "../CommandLineParameters/SaveDocumentParameters.h"

using CommandLineParameters = std::variant<
    InsertParagraphParameters,
    InsertImageParameters,
    DocumentTitle,
    ReplaceTextParameters,
    ResizeImageParameters,
    Position,
    SaveDocumentPath,
    std::monostate
>;

class CommandLineParser
{
public:
    static std::pair<ActionType, CommandLineParameters> Parse(std::istringstream& iss);
private:
    static constexpr std::string POSITION_END_IN_LINE = "|end";

    static ActionType DefineActionTypeByKeyWord(const std::string& keyword);
    static CommandLineParameters DefineCommandLineParameters(ActionType actionType, std::istringstream &iss);
    static InsertParagraphParameters ParseParamsForInsertingParagraph(std::istringstream& iss);
    static InsertImageParameters ParseParamsForInsertingImageParameters(std::istringstream& iss);
    static DocumentTitle ParseTitle(std::istringstream& iss);
    static ReplaceTextParameters ParseReplaceTextParameters(std::istringstream& iss);
    static ResizeImageParameters ParseImageParameters(std::istringstream& iss);
    static Position ParsePosition(std::istringstream& iss);
    static SaveDocumentPath ParseSaveDocumentPath(std::istringstream& iss);
};