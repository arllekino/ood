#pragma once
#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"

class CDocumentItem
{
public:
    explicit CDocumentItem(const IImagePtr& image) : m_image(image) {}
    explicit CDocumentItem(const IParagraphPtr& paragraph) : m_paragraph(paragraph) {}

    IImagePtr GetImage()
    {
        return m_image;
    }

    IParagraphPtr GetParagraph()
    {
        return m_paragraph;
    }
private:
    IImagePtr m_image;
    IParagraphPtr m_paragraph;
};

