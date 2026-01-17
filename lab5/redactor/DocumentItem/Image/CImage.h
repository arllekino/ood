#pragma once
#include "IImage.h"

class CImage : public IImage
{
public:
    CImage(const Path& path, const unsigned width, const unsigned height)
        : m_path(path),
        m_width(width),
        m_height(height)
    {
    }

    Path GetPath() const override
    {
        return m_path;
    }

    unsigned GetWidth() const override
    {
        return m_width;
    }

    unsigned GetHeight() const override
    {
        return m_height;
    }

    void Resize(const unsigned width, const unsigned height) override
    {
        m_width = width;
        m_height = height;
    }
private:
    Path m_path;
    unsigned m_width;
    unsigned m_height;
};