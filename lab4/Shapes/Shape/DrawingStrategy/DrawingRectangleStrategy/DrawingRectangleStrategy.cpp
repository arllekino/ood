//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "DrawingRectangleStrategy.h"
#include <SFML/Graphics.hpp>

DrawingRectangleStrategy::DrawingRectangleStrategy(const CPoint &startPoint, const CPoint &endPoint)
    : IDrawingStrategy(shapes::ShapeType::RECTANGLE),
    m_startPoint(startPoint),
    m_endPoint(endPoint)
{
}

void DrawingRectangleStrategy::Draw(
    const std::shared_ptr<ICanvas> canvas,
    const Color color) const
{
    canvas->SetColor(color);

    canvas->MoveTo(GetLeftTop());
    canvas->LineTo(GetRightTop());
    canvas->LineTo(GetRightBottom());
    canvas->LineTo(GetLeftBottom());
    canvas->LineTo(GetLeftTop());
}

void DrawingRectangleStrategy::MoveShape(const CPoint& deltaPoint)
{
    m_startPoint += deltaPoint;
    m_endPoint += deltaPoint;
}

std::string DrawingRectangleStrategy::GetParametersInfoAsString() const
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(2)
        << GetLeftTop().x << " "
        << GetLeftTop().y << " "
        << GetRightTop().x - GetLeftTop().x << " "
        << std::abs(GetLeftBottom().y - GetLeftTop().y);
    return os.str();
}

CPoint DrawingRectangleStrategy::GetLeftTop() const
{
    if (m_startPoint.x < m_endPoint.x)
    {
        if (m_startPoint.y < m_endPoint.y)
            return m_startPoint;
        return CPoint(m_startPoint.x, m_startPoint.y);
    }
    if (m_startPoint.y < m_endPoint.y)
        return CPoint(m_endPoint.x, m_startPoint.y);
    return m_endPoint;
}

CPoint DrawingRectangleStrategy::GetRightTop() const
{
    if (m_startPoint.x < m_endPoint.x)
    {
        if (m_startPoint.y < m_endPoint.y)
            return CPoint(m_endPoint.x, m_startPoint.y);
        return m_endPoint;
    }
    if (m_startPoint.y < m_endPoint.y)
        return m_startPoint;
    return CPoint(m_startPoint.x, m_endPoint.y);
}

CPoint DrawingRectangleStrategy::GetRightBottom() const
{
    if (m_startPoint.x < m_endPoint.x)
    {
        if (m_startPoint.y < m_endPoint.y)
            return m_endPoint;
        return CPoint(m_endPoint.x, m_startPoint.y);
    }
    if (m_startPoint.y < m_endPoint.y)
        return CPoint(m_startPoint.x, m_endPoint.y);
    return m_startPoint;
}

CPoint DrawingRectangleStrategy::GetLeftBottom() const
{
    if (m_startPoint.x < m_endPoint.x)
    {
        if (m_startPoint.y < m_endPoint.y)
            return CPoint(m_startPoint.x, m_endPoint.y);
        return m_startPoint;
    }
    if (m_startPoint.y < m_endPoint.y)
        return m_endPoint;
    return CPoint(m_endPoint.x, m_startPoint.y);
}
