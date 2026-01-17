#pragma once
#include <SFML/Graphics.hpp>

#include "../Color/Color.h"
#include "../CPoint/CPoint.h"
#include "../ICanvas/ICanvas.h"

class CCanvas final : public ICanvas
{
public:
    explicit CCanvas(sf::RenderWindow& window);
    ~CCanvas() override = default;

    void MoveTo(const CPoint& point) override;
    void SetColor(const Color& color) override;
    void LineTo(const CPoint& point) override;
    void DrawEllipse(const CPoint& position, float rx, float ry) override;
    void DrawText(const CPoint& position, float fontSize, const std::string& text) override;

private:
    const sf::Font m_font = sf::Font("/Users/miroslav.aktuganov/CLionProjects/ood/lab1/Shapes/Font/Czizh_font.ttf");
    const unsigned int m_windowWidth = 800;
    const unsigned int m_windowHeight = 600;
    sf::RenderWindow& m_window;

    Color m_penColor = Color("#FFFFFF");
    CPoint m_penPosition = CPoint(0, 0);

    static sf::Vertex ConvertPointToVertex(const CPoint& point, const Color& color);
};
