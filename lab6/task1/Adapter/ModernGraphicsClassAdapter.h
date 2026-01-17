#pragma once

#include "../graphics_lib/graphics_lib.h"
#include "../modern_graphics_lib/modern_graphics_lib.h"

class ModernGraphicsClassAdapter : public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
    explicit ModernGraphicsClassAdapter(std::ostream& strm)
        : CModernGraphicsRenderer(strm),
        m_currentPoint(0, 0),
        m_currentColor(0, 0, 0, 0)
    {
        BeginDraw();
    }

    void SetColor(uint32_t rgbColor) override
    {
        m_currentColor = {
            static_cast<float>(rgbColor >> 24 & 0xFF) / 255.0f,
            static_cast<float>(rgbColor >> 16 & 0xFF) / 255.0f,
            static_cast<float>(rgbColor >> 8 & 0xFF) / 255.0f,
            0
        };
    }

    void MoveTo(int x, int y) override
    {
        m_currentPoint = {x, y};
    }

    void LineTo(int x, int y) override
    {
        modern_graphics_lib::CPoint point = {x, y};
        DrawLine(m_currentPoint, point, m_currentColor);
        m_currentPoint = point;
    }

private:
    modern_graphics_lib::CPoint m_currentPoint;
    modern_graphics_lib::CRGBAColor m_currentColor;
};