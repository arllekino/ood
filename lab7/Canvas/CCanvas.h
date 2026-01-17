#pragma once
#include "./ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas
{
public:
    explicit Canvas(sf::RenderWindow& window)
        : m_window(window),
        m_fillColor(Color::White),
        m_lineColor(Color::Black),
        m_lineWidth(1)
    {
    }

    void SetDefaultDrawProperties() override
    {
        m_fillColor = Color::White;
        m_lineColor = Color::Black;
        m_lineWidth = 1;
    }

    void SetFillColor(const Color& color) override
    {
        m_fillColor = color;
    }

    void SetLineColor(const Color& color) override
    {
        m_lineColor = color;
    }

    void SetLineWidth(unsigned width) override
    {
        m_lineWidth = width;
    }

    void DrawLine(const Point& from, const Point& to) override
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y)), ConvertColor(m_lineColor)),
            sf::Vertex(sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y)), ConvertColor(m_lineColor))
        };

        // Для толстых линий используем прямоугольник
        if (m_lineWidth > 1) {
            DrawThickLine(from, to, m_lineWidth);
        } else {
            m_window.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }

    void DrawEllipse(const Point& center, unsigned width, unsigned height) override
    {
        sf::CircleShape ellipse(static_cast<float>(std::max(width, height) / 2));

        ellipse.setPosition({
            static_cast<float>(center.x - width / 2),
            static_cast<float>(center.y - height / 2)
        });

        ellipse.setScale({
            static_cast<float>(width) / static_cast<float>(std::max(width, height)),
            static_cast<float>(height) / static_cast<float>(std::max(width, height))
        });

        ellipse.setFillColor(ConvertColor(m_fillColor));
        ellipse.setOutlineColor(ConvertColor(m_lineColor));
        ellipse.setOutlineThickness(static_cast<float>(m_lineWidth));

        m_window.draw(ellipse);
    }

    void DrawPolygon(const std::vector<Point>& points) override
    {
        if (points.size() < 3) return;

        // Создаем выпуклый многоугольник
        sf::ConvexShape polygon;
        polygon.setPointCount(points.size());

        for (size_t i = 0; i < points.size(); ++i) {
            polygon.setPoint(i, sf::Vector2f(
                static_cast<float>(points[i].x),
                static_cast<float>(points[i].y)
            ));
        }

        polygon.setFillColor(ConvertColor(m_fillColor));
        polygon.setOutlineColor(ConvertColor(m_lineColor));
        polygon.setOutlineThickness(static_cast<float>(m_lineWidth));

        m_window.draw(polygon);
    }

private:
    sf::RenderWindow& m_window;
    const unsigned int m_WindowWidth = 800;
    const unsigned int m_WindowHeight = 600;
    Color m_fillColor;
    Color m_lineColor;
    unsigned m_lineWidth;

    static sf::Color ConvertColor(const Color& color)
    {
        uint32_t rgba = color.GetAsUint32();
        uint8_t r = (rgba >> 24) & 0xFF;
        uint8_t g = (rgba >> 16) & 0xFF;
        uint8_t b = (rgba >> 8) & 0xFF;
        uint8_t a = rgba & 0xFF;
        return {r, g, b, a};
    }

    void DrawThickLine(const Point& from, const Point& to, unsigned width)
    {
        sf::Vector2f start(static_cast<float>(from.x), static_cast<float>(from.y));
        sf::Vector2f end(static_cast<float>(to.x), static_cast<float>(to.y));

        sf::Vector2f direction = end - start;
        sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        sf::Vector2f offset = (static_cast<float>(width) / 2.0f) * unitPerpendicular;

        sf::VertexArray thickLine(sf::PrimitiveType::Triangles, 4);
        thickLine[0].position = start + offset;
        thickLine[1].position = end + offset;
        thickLine[2].position = end - offset;
        thickLine[3].position = start - offset;

        for (int i = 0; i < 4; ++i) {
            thickLine[i].color = ConvertColor(m_lineColor);
        }

        m_window.draw(thickLine);
    }
};