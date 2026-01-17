//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "DrawingLineStrategy.h"

#include <iomanip>
#include <sstream>

DrawingLineStrategy::DrawingLineStrategy(const CPoint& startPoint, const CPoint& endPoint)
    : IDrawingStrategy(shapes::ShapeType::LINE),
    m_startPoint(startPoint),
    m_endPoint(endPoint)
{
}

void DrawingLineStrategy::Draw(const std::shared_ptr<ICanvas> canvas, const Color color) const
{
    canvas->SetColor(color);

    canvas->MoveTo(m_startPoint);
    canvas->LineTo(m_endPoint);
}

void DrawingLineStrategy::MoveShape(const CPoint& deltaPoint)
{
    m_startPoint += deltaPoint;
    m_endPoint += deltaPoint;
}

std::string DrawingLineStrategy::GetParametersInfoAsString() const
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(2)
        << m_startPoint.x << " " << m_startPoint.y
        << m_endPoint.x << " " << m_endPoint.y;
    return os.str();
}
