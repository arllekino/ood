//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
    : m_window(window)
{
}

void CCanvas::MoveTo(const CPoint& point)
{
    m_penPosition = point;
}

void CCanvas::SetColor(const Color& color)
{
    m_penColor = color;
}

void CCanvas::LineTo(const CPoint& point)
{
    std::vector<sf::Vertex> line;
    line.push_back(sf::Vertex(ConvertPointToVertex(m_penPosition, m_penColor)));
    line.push_back(sf::Vertex(ConvertPointToVertex(point, m_penColor)));
    m_penPosition = point;

    m_window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}

void CCanvas::DrawEllipse(const CPoint& position, const float rx, const float ry)
{
    sf::CircleShape ellipse(rx);
    ellipse.setScale({ 1.0f, ry / rx });
    ellipse.setPosition({ position.x - rx, position.y - ry });
    ellipse.setFillColor(sf::Color(m_penColor.GetAsUint32()));

    m_window.draw(ellipse);
}

void CCanvas::DrawText(const CPoint& position, const float fontSize, const std::string& text)
{
    sf::Text textShape(m_font, text);
    textShape.setPosition({ position.x, position.y });
    textShape.setFillColor(sf::Color(m_penColor.GetAsUint32()));
    textShape.setCharacterSize(static_cast<int>(fontSize));

    m_window.draw(textShape);
}

sf::Vertex CCanvas::ConvertPointToVertex(const CPoint& point, const Color& color)
{
    return sf::Vertex(
        { point.x, point.y },
        sf::Color(color.GetAsUint32())
    );
}
