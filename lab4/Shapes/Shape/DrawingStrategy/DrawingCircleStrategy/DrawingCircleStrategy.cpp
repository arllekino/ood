//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include <SFML/Graphics.hpp>
#include "DrawingCircleStrategy.h"
#include "../../../CPoint/CPoint.h"

DrawingCircleStrategy::DrawingCircleStrategy(const CPoint& center, const float radius)
    : IDrawingStrategy(shapes::ShapeType::CIRCLE),
    m_center(center),
    m_radius(radius)
{
    if (radius < 0)
    {
        throw std::invalid_argument("Radius must be positive");
    }
}

void DrawingCircleStrategy::Draw(const std::shared_ptr<ICanvas> canvas, const Color color) const
{
    canvas->SetColor(color);
    canvas->DrawEllipse(m_center, m_radius, m_radius);
}

void DrawingCircleStrategy::MoveShape(const CPoint &deltaPoint)
{
    m_center += deltaPoint;
}

std::string DrawingCircleStrategy::GetParametersInfoAsString() const
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(2)
        << std::to_string(m_center.x) << " "
        << std::to_string(m_center.y) << " "
        << std::to_string(m_radius);
    return os.str();
}
