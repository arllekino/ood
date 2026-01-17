#pragma once
#include "ICommand.h"
#include "../CommandLineParameters/InsertImageParameters.h"
#include "../Document/IDocument.h"

class IDocument;

class InsertImageCommand : public ICommand
{
public:
    InsertImageCommand(const IDocumentPtr& document, const InsertImageParameters& parameters)
        : m_document(document),
        m_parameters(parameters)
    {
    }

    void Execute() override
    {
        m_document->InsertImage(
            m_parameters.path,
            m_parameters.width,
            m_parameters.height,
            m_parameters.pos
        );
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
    InsertImageParameters m_parameters;
};

// добавить логику с сохранением картинки при добавлении