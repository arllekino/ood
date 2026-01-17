//
// Created by Miroslav Aktuganov on 18.10.2025.
//

#include <iostream>
#include <catch2/catch_all.hpp>
#include "../Shape/Shape.h"
#include "../Shape/DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.h"
#include "../ICanvas/ICanvas.h"

class TestCanvas : public ICanvas
{
public:
    void MoveTo(const CPoint& point) override
    {
        m_moveToCalls++;
        m_lastMoveTo = point;
    }

    void SetColor(const Color& color) override
    {
        m_setColorCalls++;
        m_lastColor = color;
    }

    void LineTo(const CPoint& point) override
    {
        m_lineToCalls++;
        m_lastLineTo = point;
    }

    void DrawEllipse(const CPoint& position, float rx, float ry) override
    {
        m_drawEllipseCalls++;
        m_lastEllipsePosition = position;
        m_lastEllipseRx = rx;
        m_lastEllipseRy = ry;
    }

    void DrawText(const CPoint& position, float fontSize, const std::string& text) override
    {
        m_drawTextCalls++;
        m_lastTextPosition = position;
        m_lastFontSize = fontSize;
        m_lastText = text;
    }

    int m_moveToCalls = 0;
    int m_setColorCalls = 0;
    int m_lineToCalls = 0;
    int m_drawEllipseCalls = 0;
    int m_drawTextCalls = 0;

    CPoint m_lastMoveTo;
    CPoint m_lastLineTo;
    Color m_lastColor = Color("#FFFFFF");
    CPoint m_lastEllipsePosition;
    float m_lastEllipseRx = 0;
    float m_lastEllipseRy = 0;
    CPoint m_lastTextPosition;
    float m_lastFontSize = 0;
    std::string m_lastText;
};

TEST_CASE("Shape class tests")
{
    auto testCanvas = std::make_shared<TestCanvas>();

    auto strategy = std::make_unique<DrawingLineStrategy>(CPoint{0,0}, CPoint{10,10});
    shapes::Shape shape(std::move(strategy), "line1", Color("#FF0000"));

    SECTION("GetId returns correct id")
    {
        REQUIRE(shape.GetId() == "line1");
    }

    SECTION("GetColor returns correct color")
    {
        REQUIRE(shape.GetColor().GetAsUint32() == 0xFF0000FF);
    }

    SECTION("SetColor updates color")
    {
        shape.SetColor(Color("#00FF00"));
        REQUIRE(shape.GetColor().GetAsUint32() == 0x00FF00FF);
    }

    SECTION("Draw calls strategy Draw method")
    {
        testCanvas->m_moveToCalls = 0;
        testCanvas->m_setColorCalls = 0;
        testCanvas->m_lineToCalls = 0;

        shape.Draw(testCanvas);

        REQUIRE(testCanvas->m_setColorCalls == 1);
        REQUIRE(testCanvas->m_moveToCalls == 1);
        REQUIRE(testCanvas->m_lineToCalls == 1);
    }
}