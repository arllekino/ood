#pragma once
#include "ICommand.h"
#include "../CommandLineParameters/SetTitleParameters.h"
#include "../Document/IDocument.h"

class SetTitleCommand : public ICommand
{
public:
    SetTitleCommand(
        const IDocumentPtr& document,
        const DocumentTitle& title)
        : m_document(document),
        m_newTitle(title)
    {
        m_previousTitle = m_document->GetTitle();
    }

    void Execute() override
    {
        m_document->SetTitle(m_newTitle);
    }

    void Unexecute() override
    {
        m_document->SetTitle(m_previousTitle);
    }
private:
    IDocumentPtr m_document;
    DocumentTitle m_newTitle;
    DocumentTitle m_previousTitle;
};
