#pragma once
#include <optional>

#include "IShape.h"
#include "../Canvas/ICanvas.h"
#include "../Point/Point.h"

class Ellipse : public IShape
{
public:
    Ellipse(const Point& center, unsigned width, unsigned height)
        : m_center(center), m_width(width), m_height(height)
    {
        UpdateBorderRect();
    };

    void Draw(ICanvas& canvas) override
    {
        AssertFillStyleOrLineStyleExist();
        canvas.SetDefaultDrawProperties();
        if (m_fillStyle.has_value())
        {
            canvas.SetFillColor(m_fillStyle.value().color);
        }
        if (m_lineStyle.has_value())
        {
            canvas.SetLineColor(m_lineStyle.value().color);
            canvas.SetLineWidth(m_lineStyle.value().width);
        }
        canvas.DrawEllipse(m_center, m_width, m_height);
    }

    void SetFillStyle(const std::optional<FillStyle>& fillStyle) override
    {
        m_fillStyle = fillStyle;
    }

    std::optional<FillStyle> GetFillStyle() override
    {
        return m_fillStyle;
    }

    void SetLineStyle(const std::optional<LineStyle>& lineStyle) override
    {
        m_lineStyle = lineStyle;
    }

    std::optional<LineStyle> GetLineStyle() override
    {
        return m_lineStyle;
    }

    BorderRectangle GetBorderRect() override
    {
        return m_borderRect;
    }

    void SetBorderRect(const BorderRectangle& borderRect) override
    {
        m_borderRect = borderRect;
        m_center = Point(
            m_borderRect.GetLeftTop().x + m_borderRect.GetWidth() / 2,
            m_borderRect.GetLeftTop().y + m_borderRect.GetHeight() / 2
        );
        m_width = m_borderRect.GetWidth();
        m_height = m_borderRect.GetHeight();
    }

    [[nodiscard]] std::shared_ptr<IShape> Clone() const override
    {
        auto clone = std::make_shared<Ellipse>(m_center, m_width, m_height);
        if (m_fillStyle)
        {
            clone->SetFillStyle(*m_fillStyle);
        }
        if (m_lineStyle)
        {
            clone->SetLineStyle(*m_lineStyle);
        }
        return clone;
    }

private:
    BorderRectangle m_borderRect{{0, 0}, 0, 0};
    Point m_center;
    unsigned m_width;
    unsigned m_height;
    std::optional<FillStyle> m_fillStyle;
    std::optional<LineStyle> m_lineStyle;

    void AssertFillStyleOrLineStyleExist() const
    {
        if (!m_fillStyle.has_value() && !m_lineStyle.has_value())
        {
            throw std::logic_error("No fill style or line style exist before drawing");
        }
    }

    void UpdateBorderRect()
    {
        m_borderRect = BorderRectangle(
            Point(m_center.x - m_width / 2, m_center.y - m_height / 2),
            m_width,
            m_height
        );
    }
};