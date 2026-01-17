#pragma once
#include "ICommand.h"
#include "../CommandLineParameters/ResizeImageParameters.h"
#include "../Document/IDocument.h"

class ResizeImageCommand : public ICommand
{
public:
    ResizeImageCommand(
        const IDocumentPtr& document,
        const ResizeImageParameters& parameters)
        : m_document(document),
        m_newParameters(parameters)
    {
        auto item = m_document->GetItem(parameters.pos);
        if (const auto image = item.GetImage(); image != nullptr)
        {
            m_path = image->GetPath();
            m_oldParameters = {
                parameters.pos,
                image->GetWidth(),
                image->GetHeight()
            };
        }
        else
        {
            throw std::invalid_argument("No image found");
        }
    }

    void Execute() override
    {
        auto item = m_document->GetItem(m_newParameters.pos);
        if (const auto image = item.GetImage())
        {
            image->Resize(m_newParameters.width, m_newParameters.height);
        }
    }

    void Unexecute() override
    {
        auto item = m_document->GetItem(m_newParameters.pos);
        if (const auto image = item.GetImage())
        {
            image->Resize(m_oldParameters.width, m_oldParameters.height);
        }
    }
private:
    IDocumentPtr m_document;
    ResizeImageParameters m_oldParameters;
    ResizeImageParameters m_newParameters;
    Path m_path;
};
