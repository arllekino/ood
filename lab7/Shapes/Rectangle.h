#pragma once
#include <optional>
#include <vector>

#include "IShape.h"
#include "../Point/Point.h"

class Rectangle : public IShape
{
public:
    Rectangle(const Point& leftTop, unsigned width, unsigned height)
        : m_borderRect(leftTop, width, height)
    {
    }

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
        canvas.DrawPolygon(CreatePoints());
    }

    void SetLineStyle(const std::optional<LineStyle> &lineStyle) override
    {
        m_lineStyle = lineStyle;
    }

    std::optional<LineStyle> GetLineStyle() override
    {
        return m_lineStyle;
    }

    void SetFillStyle(const std::optional<FillStyle> &fillStyle) override
    {
        m_fillStyle = fillStyle;
    }

    std::optional<FillStyle> GetFillStyle() override
    {
        return m_fillStyle;
    }

    BorderRectangle GetBorderRect() override
    {
        return m_borderRect;
    }

    void SetBorderRect(const BorderRectangle& borderRect) override
    {
        m_borderRect = borderRect;
    }

    [[nodiscard]] std::shared_ptr<IShape> Clone() const override
    {
        auto clone = std::make_shared<Rectangle>(
            m_borderRect.GetLeftTop(),
            m_borderRect.GetWidth(),
            m_borderRect.GetHeight()
        );
        if (m_fillStyle.has_value())
        {
            clone->SetFillStyle(m_fillStyle.value());
        }
        if (m_lineStyle.has_value())
        {
            clone->SetLineStyle(m_lineStyle.value());
        }
        return clone;
    }

private:
    BorderRectangle m_borderRect;
    std::optional<FillStyle> m_fillStyle;
    std::optional<LineStyle> m_lineStyle;

    void AssertFillStyleOrLineStyleExist() const
    {
        if (!m_fillStyle.has_value() && !m_lineStyle.has_value())
        {
            throw std::logic_error("No fill style or line style exist before drawing");
        }
    }

    [[nodiscard]] std::vector<Point> CreatePoints() const
    {
        const auto leftTop = m_borderRect.GetLeftTop();
        const auto width = m_borderRect.GetWidth();
        const auto height = m_borderRect.GetHeight();

        return {
            leftTop,
            { leftTop.x + width, leftTop.y },
            { leftTop.x + width, leftTop.y + height },
            { leftTop.x, leftTop.y + height },
        };
    }
};
