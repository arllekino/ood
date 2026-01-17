#pragma once
#include <algorithm>

#include "./IShape.h"

class Triangle : public IShape
{
public:
    Triangle(const Point& point1, const Point& point2, const Point& point3)
        : m_borderRect(GetUpdateBorderRect(point1, point2, point3)),
        m_point1(point1),
        m_point2(point2),
        m_point3(point3)
    {
    }

    void Draw(ICanvas& canvas) override
    {
        AssertFillStyleOrLineStyleExist();
        if (m_fillStyle.has_value())
        {
            canvas.SetFillColor(m_fillStyle.value().color);
        }
        if (m_lineStyle.has_value())
        {
            canvas.SetLineColor(m_lineStyle.value().color);
            canvas.SetLineWidth(m_lineStyle.value().width);
        }
        canvas.DrawPolygon({ m_point1, m_point2, m_point3 });
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
        auto oldRect = GetBorderRect();

        if (oldRect.GetWidth() == 0 || oldRect.GetHeight() == 0)
        {
            m_borderRect = borderRect;
            return;
        }

        double scaleX = static_cast<double>(borderRect.GetWidth()) / oldRect.GetWidth();
        double scaleY = static_cast<double>(borderRect.GetHeight()) / oldRect.GetHeight();

        Point oldLeftTop = oldRect.GetLeftTop();
        Point newLeftTop = borderRect.GetLeftTop();

        m_point1.x = static_cast<int>(newLeftTop.x + (m_point1.x - oldLeftTop.x) * scaleX);
        m_point1.y = static_cast<int>(newLeftTop.y + (m_point1.y - oldLeftTop.y) * scaleY);

        m_point2.x = static_cast<int>(newLeftTop.x + (m_point2.x - oldLeftTop.x) * scaleX);
        m_point2.y = static_cast<int>(newLeftTop.y + (m_point2.y - oldLeftTop.y) * scaleY);

        m_point3.x = static_cast<int>(newLeftTop.x + (m_point3.x - oldLeftTop.x) * scaleX);
        m_point3.y = static_cast<int>(newLeftTop.y + (m_point3.y - oldLeftTop.y) * scaleY);

        m_borderRect = borderRect;
    }

    [[nodiscard]] std::shared_ptr<IShape> Clone() const override
    {
        auto clone = std::make_shared<Triangle>(m_point1, m_point2, m_point3);
        if (m_lineStyle.has_value())
        {
            clone->SetLineStyle(m_lineStyle.value());
        }
        if (m_fillStyle.has_value())
        {
            clone->SetFillStyle(m_fillStyle.value());
        }
        return clone;
    }

private:
    BorderRectangle m_borderRect;
    Point m_point1;
    Point m_point2;
    Point m_point3;
    std::optional<LineStyle> m_lineStyle;
    std::optional<FillStyle> m_fillStyle;

    static BorderRectangle GetUpdateBorderRect(const Point& point1, const Point& point2, const Point& point3)
    {
        const auto minY = std::min({point1.y, point2.y, point3.y});
        const auto maxY = std::max({point1.y, point2.y, point3.y});
        const auto minX = std::min({point1.x, point2.x, point3.x});
        const auto maxX = std::max({point1.x, point2.x, point3.x});

        return { { minX, minY }, maxX - minX, maxY - minY };
    }

    void AssertFillStyleOrLineStyleExist() const
    {
        if (!m_fillStyle.has_value() && !m_lineStyle.has_value())
        {
            throw std::logic_error("No fill style or line style exist before drawing");
        }
    }
};