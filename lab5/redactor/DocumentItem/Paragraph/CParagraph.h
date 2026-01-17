#pragma once
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
    explicit CParagraph(const std::string& text) : IParagraph(), m_text(text)
    {
    }

    std::string GetText() const override
    {
        return m_text;
    }

    void SetText(const std::string& text) override
    {
        m_text = text;
    }

private:
    std::string m_text;
};