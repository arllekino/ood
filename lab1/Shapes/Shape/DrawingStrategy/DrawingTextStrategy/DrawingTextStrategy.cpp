//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "DrawingTextStrategy.h"
#include <SFML/Graphics.hpp>

DrawingTextStrategy::DrawingTextStrategy(
    std::string text,
    const float fontSize,
    const CPoint& position)
        : IDrawingStrategy(shapes::ShapeType::TEXT),
        m_text(std::move(text)),
        m_fontSize(fontSize),
        m_position(position)
{
}

void DrawingTextStrategy::Draw(const std::shared_ptr<ICanvas> canvas, const Color color) const
{
    canvas->SetColor(color);
    canvas->DrawText(m_position, m_fontSize, m_text);
}

void DrawingTextStrategy::MoveShape(const CPoint& deltaPoint)
{
    m_position += deltaPoint;
}

std::string DrawingTextStrategy::GetParametersInfoAsString() const
{
    std::ostringstream os;
    os << m_position.x << " "
        << m_position.y << " "
        << m_fontSize
        << m_text;
    return os.str();
}
