//
// Created by Miroslav Aktuganov on 15.10.2025.
//

#include "DrawingPolygonStrategy.h"
#include <iomanip>
#include <sstream>

DrawingPolygonStrategy::DrawingPolygonStrategy(
    const CPoint &center,
    const unsigned edgesCount,
    const float radius)
    : IDrawingStrategy(shapes::ShapeType::POLYGON),
        m_center(center),
        m_radius(radius),
        m_edgesCount(edgesCount)
{
    if (edgesCount < 3)
    {
        throw std::invalid_argument("Cannot draw polygon with edges count less than 3");
    }
}

void DrawingPolygonStrategy::Draw(
    std::shared_ptr<ICanvas> canvas,
    const Color color) const
{
    canvas->SetColor(color);

    std::vector<CPoint> vertices;
    const auto angleIncrement = static_cast<float>(2 * M_PI / m_edgesCount);

    for (size_t i = 0; i < m_edgesCount; ++i)
    {
        const float angle = angleIncrement * static_cast<float>(i);
        float x = m_center.x + std::cos(angle) * m_radius;
        float y = m_center.y + std::sin(angle) * m_radius;
        vertices.emplace_back(x, y);
    }

    canvas->MoveTo(vertices[0]);
    for (size_t i = 1; i < vertices.size(); ++i)
    {
        canvas->LineTo(vertices[i]);
    }
    canvas->LineTo(vertices[0]);
}

void DrawingPolygonStrategy::MoveShape(const CPoint& deltaPoint)
{
    m_center += deltaPoint;
}

std::string DrawingPolygonStrategy::GetParametersInfoAsString() const
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(2)
        << m_center.x << " " << m_center.y << " "
        << m_radius << " "
        << m_edgesCount;
    return os.str();
}
