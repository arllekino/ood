#pragma once
#include "ICommand.h"
#include "../CommandLineParameters/InsertParagraphParameters.h"
#include "../Document/IDocument.h"

class InsertParagraphCommand : public ICommand
{
public:
    InsertParagraphCommand(
        const IDocumentPtr& document,
        const InsertParagraphParameters& parameters)
        : m_document(document),
        m_parameters(parameters)
    {
    }

    void Execute() override
    {
        m_document->InsertParagraph(m_parameters.text, m_parameters.pos);
    }

    void Unexecute() override
    {
        m_document->DeleteItem(
            m_parameters.pos.has_value()
                ? m_parameters.pos.value() - 1
                : m_document->GetItemsCount() - 1
        );
    }
private:
    IDocumentPtr m_document;
    InsertParagraphParameters m_parameters;
};
