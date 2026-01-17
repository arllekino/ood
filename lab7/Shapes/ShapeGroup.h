#pragma once
#include <algorithm>
#include <memory>
#include <limits>
#include "IShape.h"

class ShapeGroup : public IShape, public IContainerable
{
public:
    void AddShape(const std::shared_ptr<IShape>& shape) override
    {
        m_shapes.push_back(shape);
    }

    void Draw(ICanvas& canvas) override
    {
        for (auto& shape : m_shapes)
        {
            shape->Draw(canvas);
        }
    }

    void SetLineStyle(const std::optional<LineStyle>& lineStyle) override
    {
        for (auto& shape : m_shapes)
        {
            shape->SetLineStyle(lineStyle);
        }
    }

    std::optional<LineStyle> GetLineStyle() override
    {
        if (m_shapes.empty()) return std::nullopt;

        auto firstStyle = m_shapes.front()->GetLineStyle();
        for (const auto& shape : m_shapes)
        {
            if (shape->GetLineStyle() != firstStyle)
            {
                return std::nullopt;
            }
        }
        return firstStyle;
    }

    void SetFillStyle(const std::optional<FillStyle>& fillStyle) override
    {
        for (auto& shape : m_shapes)
        {
            shape->SetFillStyle(fillStyle);
        }
    }

    std::optional<FillStyle> GetFillStyle() override
    {
        if (m_shapes.empty()) return std::nullopt;

        auto firstStyle = m_shapes.front()->GetFillStyle();
        for (const auto& shape : m_shapes)
        {
            if (shape->GetFillStyle() != firstStyle)
            {
                return std::nullopt;
            }
        }
        return firstStyle;
    }

    BorderRectangle GetBorderRect() override
    {
        if (m_shapes.empty()) return {{0, 0}, 0, 0};

        unsigned minX = std::numeric_limits<unsigned>::max();
        unsigned minY = std::numeric_limits<unsigned>::max();
        unsigned maxX = std::numeric_limits<unsigned>::min();
        unsigned maxY = std::numeric_limits<unsigned>::min();

        for (const auto& shape : m_shapes)
        {
            auto rect = shape->GetBorderRect();
            auto leftTop = rect.GetLeftTop();
            auto rightBottom = leftTop.x + rect.GetWidth();
            auto bottom = leftTop.y + rect.GetHeight();

            minX = std::min(minX, leftTop.x);
            minY = std::min(minY, leftTop.y);
            maxX = std::max(maxX, rightBottom);
            maxY = std::max(maxY, bottom);
        }

        return {{minX, minY}, static_cast<unsigned>(maxX - minX), static_cast<unsigned>(maxY - minY)};
    }

    void SetBorderRect(const BorderRectangle& rect) override
    {
        auto oldRect = GetBorderRect();
        if (oldRect.GetWidth() == 0 || oldRect.GetHeight() == 0) return;

        double scaleX = static_cast<double>(rect.GetWidth()) / oldRect.GetWidth();
        double scaleY = static_cast<double>(rect.GetHeight()) / oldRect.GetHeight();

        for (auto& shape : m_shapes)
        {
            auto childRect = shape->GetBorderRect();
            auto oldChildLeftTop = childRect.GetLeftTop();

            unsigned newChildX = static_cast<unsigned>(rect.GetLeftTop().x + (oldChildLeftTop.x - oldRect.GetLeftTop().x) * scaleX);
            unsigned newChildY = static_cast<unsigned>(rect.GetLeftTop().y + (oldChildLeftTop.y - oldRect.GetLeftTop().y) * scaleY);
            unsigned newChildWidth = static_cast<unsigned>(childRect.GetWidth() * scaleX);
            unsigned newChildHeight = static_cast<unsigned>(childRect.GetHeight() * scaleY);

            shape->SetBorderRect({{newChildX, newChildY}, newChildWidth, newChildHeight});
        }
    }

    std::shared_ptr<IShape> Clone() const override
    {
        auto clone = std::make_shared<ShapeGroup>();
        for (const auto& shape : m_shapes)
        {
            clone->AddShape(shape->Clone());
        }
        return clone;
    }

    size_t GetShapeCount() const { return m_shapes.size(); }

private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
};