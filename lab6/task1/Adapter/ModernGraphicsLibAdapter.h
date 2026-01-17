#pragma once
#include "../graphics_lib/graphics_lib.h"
#include "../modern_graphics_lib/modern_graphics_lib.h"

namespace app
{
    class ModernGraphicsLibAdapter : public graphics_lib::ICanvas
    {
    public:
        explicit ModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
            : m_renderer(renderer),
            m_currentPoint(0, 0),
            m_currentColor(0, 0, 0, 0)
        {
            m_renderer.BeginDraw();
        }

        ~ModernGraphicsLibAdapter() override
        {
            m_renderer.EndDraw();
        }

        void SetColor(uint32_t rgbColor) override
        {
            m_currentColor = {
                static_cast<float>(rgbColor >> 24 & 0xFF) / 255.0f,
                static_cast<float>((rgbColor >> 16) & 0xFF) / 255.0f,
                static_cast<float>((rgbColor >> 8) & 0xFF) / 255.0f,
                0
            };
        }

        void MoveTo(int x, int y) override
        {
            m_currentPoint = {x, y};
        }

        void LineTo(int x, int y) override
        {
            modern_graphics_lib::CPoint newPoint = {x, y};
            m_renderer.DrawLine(m_currentPoint, newPoint, m_currentColor);
            m_currentPoint = newPoint;
        }
    private:
        modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
        modern_graphics_lib::CPoint m_currentPoint;
        modern_graphics_lib::CRGBAColor m_currentColor;
    };
}
