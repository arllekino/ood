#pragma once
#include "ICommand.h"
#include "../CommandLineParameters/ReplaceTextParamaters.h"
#include "../Document/IDocument.h"

class ReplaceTextCommand : public ICommand
{
public:
    ReplaceTextCommand(
        const IDocumentPtr& document,
        const ReplaceTextParameters& parameters)
        : m_document(document),
        m_newParameters(parameters)
    {
        auto item = m_document->GetItem(parameters.pos);
        if (const auto paragraph = item.GetParagraph(); paragraph != nullptr)
        {
            m_oldParameters = {
                parameters.pos,
                paragraph->GetText(),
            };
        }
        else
        {
            throw std::invalid_argument("No paragraph found");
        }
    }

    void Execute() override
    {
        auto item = m_document->GetItem(m_newParameters.pos);
        if (const auto paragraph = item.GetParagraph())
        {
            paragraph->SetText(m_newParameters.text);
        }
    }

    void Unexecute() override
    {
        auto item = m_document->GetItem(m_newParameters.pos);
        if (const auto paragraph = item.GetParagraph())
        {
            paragraph->SetText(m_oldParameters.text);
        }
    }
private:
    IDocumentPtr m_document;
    ReplaceTextParameters m_newParameters;
    ReplaceTextParameters m_oldParameters;
};
