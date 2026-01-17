//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "DrawingTriangleStrategy.h"
#include <SFML/Graphics.hpp>

DrawingTriangleStrategy::DrawingTriangleStrategy(
    const CPoint& vertex1,
    const CPoint& vertex2,
    const CPoint& vertex3)
        : IDrawingStrategy(shapes::ShapeType::TRIANGLE),
        m_vertex1(vertex1),
        m_vertex2(vertex2),
        m_vertex3(vertex3)
{
}

void DrawingTriangleStrategy::Draw(const std::shared_ptr<ICanvas> canvas, Color color) const
{
    canvas->SetColor(color);

    canvas->MoveTo(m_vertex1);
    canvas->LineTo(m_vertex2);
    canvas->LineTo(m_vertex3);
    canvas->LineTo(m_vertex1);
}

void DrawingTriangleStrategy::MoveShape(const CPoint &deltaPoint)
{
    m_vertex1 += deltaPoint;
    m_vertex2 += deltaPoint;
    m_vertex3 += deltaPoint;
}

std::string DrawingTriangleStrategy::GetParametersInfoAsString() const
{
    std::ostringstream os;
    os << m_vertex1.x << " "
        << m_vertex1.y << " "
        << m_vertex2.x << " "
        << m_vertex2.y << " "
        << m_vertex3.x << " "
        << m_vertex3.y << " ";
    return os.str();
}