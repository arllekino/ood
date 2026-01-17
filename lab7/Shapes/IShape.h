#pragma once
#include "../Canvas/IDrawable.h"
#include "./ShapeProperties/FillStyle.h"
#include "./ShapeProperties/LineStyle.h"
#include "ICloneable/ICloneable.h"

class BorderRectangle;

class IShape : public IDrawable, public ICloneable<std::shared_ptr<IShape>>
{
public:
    void Draw(ICanvas& canvas) override = 0;
    virtual void SetLineStyle(const std::optional<LineStyle> &lineStyle) = 0;
    virtual std::optional<LineStyle> GetLineStyle() = 0;
    virtual void SetFillStyle(const std::optional<FillStyle> &fillStyle) = 0;
    virtual std::optional<FillStyle> GetFillStyle() = 0;
    virtual BorderRectangle GetBorderRect() = 0;
    virtual void SetBorderRect(const BorderRectangle& borderRect) = 0;
};

class BorderRectangle : public IShape
{
public:
    BorderRectangle(const Point& leftTop, const unsigned width, const unsigned height)
        : m_leftTop(leftTop),
        m_width(width),
        m_height(height)
    {
    }

    void Draw(ICanvas &canvas) override
    {
        canvas.SetDefaultDrawProperties();
        canvas.SetLineColor(Color::Black);
        canvas.SetLineWidth(1);
        canvas.DrawPolygon(CreatePoints());
    }

    void SetLineStyle(const std::optional<LineStyle> &lineStyle) override {}
    std::optional<LineStyle> GetLineStyle() override { return std::nullopt; }
    void SetFillStyle(const std::optional<FillStyle> &fillStyle) override {}
    std::optional<FillStyle> GetFillStyle() override { return std::nullopt; }
    BorderRectangle GetBorderRect() override { return *this; }

    void SetBorderRect(const BorderRectangle& borderRect) override
    {
        m_leftTop = borderRect.m_leftTop;
        m_width = borderRect.m_width;
        m_height = borderRect.m_height;
    }

    [[nodiscard]] std::shared_ptr<IShape> Clone() const override
    {
        auto clone = std::make_shared<BorderRectangle>(m_leftTop, m_width, m_height);
        return clone;
    }

    [[nodiscard]] Point GetLeftTop() const
    {
        return m_leftTop;
    }

    [[nodiscard]] unsigned GetWidth() const
    {
        return m_width;
    }

    [[nodiscard]] unsigned GetHeight() const
    {
        return m_height;
    }

private:
    Point m_leftTop;
    unsigned int m_width;
    unsigned int m_height;

    [[nodiscard]] std::vector<Point> CreatePoints() const
    {
        return {
            m_leftTop,
            { m_leftTop.x + m_width, m_leftTop.y },
            { m_leftTop.x + m_width, m_leftTop.y + m_height },
            { m_leftTop.x, m_leftTop.y + m_height },
        };
    }
};
