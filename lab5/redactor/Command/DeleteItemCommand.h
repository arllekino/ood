#pragma once

#include "ICommand.h"
#include "../CommandLineParameters/Position.h"
#include "../Document/IDocument.h"

class DeleteItemCommand : public ICommand
{
public:
    DeleteItemCommand(
        IDocumentPtr document,
        const Position position)
        : m_document(std::move(document)),
        m_position(position)
    {
        m_item = m_document->GetItem(m_position);
        if (m_item->GetImage() == nullptr && m_item->GetParagraph() == nullptr)
        {
            throw std::invalid_argument("Invalid item position");
        }
    }

    void Execute() override
    {
        m_document->DeleteItem(m_position);
    }

    void Unexecute() override
    {
        if (const auto image = m_item->GetImage(); image != nullptr)
        {
            m_document->InsertImage(
                image->GetPath(),
                image->GetWidth(),
                image->GetHeight(),
                m_position
            );
            return;
        }
        if (const auto paragraph = m_item->GetParagraph(); paragraph != nullptr)
        {
            m_document->InsertParagraph(
                paragraph->GetText(),
                m_position
            );
            return;
        }
        throw std::invalid_argument("Invalid item given trying to unexecute item deletion");
    }
private:
    IDocumentPtr m_document;
    Position m_position;
    std::optional<CDocumentItem> m_item;
};
