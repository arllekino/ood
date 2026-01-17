#pragma once

#include "../graphics_lib/graphics_lib.h"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
    struct Point
    {
        int x;
        int y;
    };

    class ICanvasDrawable
    {
    public:
        virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
        virtual ~ICanvasDrawable() = default;
    };

    class CTriangle : public ICanvasDrawable
    {
    public:
        CTriangle(const Point& p1, const Point& p2, const Point& p3, const uint32_t rgbColor)
            : m_p1(p1), m_p2(p2), m_p3(p3), m_rgbColor(rgbColor)
        {
        }

        void Draw(graphics_lib::ICanvas& canvas) const override
        {
            canvas.SetColor(m_rgbColor);

            canvas.MoveTo(m_p1.x, m_p1.y);
            canvas.LineTo(m_p2.x, m_p2.y);
            canvas.LineTo(m_p3.x, m_p3.y);
            canvas.LineTo(m_p1.x, m_p1.y);
        }
    private:
        const Point m_p1;
        const Point m_p2;
        const Point m_p3;
        const uint32_t m_rgbColor;
    };

    class CRectangle : public ICanvasDrawable
    {
    public:
        CRectangle(const Point& leftTop, int width, int height, const uint32_t rgbColor)
            : m_leftTop(leftTop), m_width(width), m_height(height), m_rgbColor(rgbColor)
        {
        }

        void Draw(graphics_lib::ICanvas& canvas) const override
        {
            canvas.SetColor(m_rgbColor);

            canvas.MoveTo(m_leftTop.x, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y);
        }
    private:
        const Point m_leftTop;
        const int m_width;
        const int m_height;
        const uint32_t m_rgbColor;
    };

    class CCanvasPainter
    {
    public:
        explicit CCanvasPainter(graphics_lib::ICanvas& canvas)
            : m_canvas(canvas)
        {
        }

        void Draw(const ICanvasDrawable& drawable) const
        {
            drawable.Draw(m_canvas);
        }
    private:
        graphics_lib::ICanvas& m_canvas;
    };
}