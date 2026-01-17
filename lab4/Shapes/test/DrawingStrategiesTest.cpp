//
// Created by Miroslav Aktuganov on 18.10.2025.
//
#include <catch2/catch_all.hpp>
#include "../Shape/DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.h"
#include "../Shape/DrawingStrategy/DrawingCircleStrategy/DrawingCircleStrategy.h"
#include "../Shape/DrawingStrategy/DrawingRectangleStrategy/DrawingRectangleStrategy.h"
#include "../Shape/DrawingStrategy/DrawingPolygonStrategy/DrawingPolygonStrategy.h"
#include "../ICanvas/ICanvas.h"

class TestCanvas : public ICanvas {
public:
    void MoveTo(const CPoint& point) override
    {
        m_moveToCalls++;
        m_lastMoveTo = point;
        m_moveToPoints.push_back(point);
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
        m_lineToPoints.push_back(point);
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

    void Reset()
    {
        m_moveToCalls = 0;
        m_setColorCalls = 0;
        m_lineToCalls = 0;
        m_drawEllipseCalls = 0;
        m_drawTextCalls = 0;

        m_moveToPoints.clear();
        m_lineToPoints.clear();

        m_lastMoveTo = CPoint{0, 0};
        m_lastLineTo = CPoint{0, 0};
        m_lastColor = Color("#000000");
        m_lastEllipsePosition = CPoint{0, 0};
        m_lastEllipseRx = 0;
        m_lastEllipseRy = 0;
        m_lastTextPosition = CPoint{0, 0};
        m_lastFontSize = 0;
        m_lastText = "";
    }

    int m_moveToCalls = 0;
    int m_setColorCalls = 0;
    int m_lineToCalls = 0;
    int m_drawEllipseCalls = 0;
    int m_drawTextCalls = 0;

    CPoint m_lastMoveTo;
    CPoint m_lastLineTo;
    Color m_lastColor = Color("#000000");
    CPoint m_lastEllipsePosition;
    float m_lastEllipseRx = 0;
    float m_lastEllipseRy = 0;
    CPoint m_lastTextPosition;
    float m_lastFontSize = 0;
    std::string m_lastText;

    std::vector<CPoint> m_moveToPoints;
    std::vector<CPoint> m_lineToPoints;
};

TEST_CASE("DrawingLineStrategy tests")
{
    auto testCanvas = std::make_shared<TestCanvas>();

    CPoint start{0.0f, 0.0f};
    CPoint end{10.0f, 10.0f};
    DrawingLineStrategy strategy(start, end);
    Color color("#FF0000");

    SECTION("Draw method calls canvas methods")
    {
        testCanvas->Reset();
        strategy.Draw(testCanvas, color);

        REQUIRE(testCanvas->m_setColorCalls == 1);
        REQUIRE(testCanvas->m_moveToCalls == 1);
        REQUIRE(testCanvas->m_lineToCalls == 1);

        REQUIRE(testCanvas->m_lastColor.GetAsUint32() == color.GetAsUint32());
        REQUIRE(testCanvas->m_lastMoveTo.x == start.x);
        REQUIRE(testCanvas->m_lastMoveTo.y == start.y);
        REQUIRE(testCanvas->m_lastLineTo.x == end.x);
        REQUIRE(testCanvas->m_lastLineTo.y == end.y);
    }

    SECTION("MoveShape updates points")
    {
        CPoint delta{5.0f, 5.0f};
        strategy.MoveShape(delta);

        std::string params = strategy.GetParametersInfoAsString();
        REQUIRE(params.find("5.00 5.00") != std::string::npos);
        REQUIRE(params.find("15.00 15.00") != std::string::npos);
    }

    SECTION("GetParametersInfoAsString returns correct format")
    {
        std::string params = strategy.GetParametersInfoAsString();
        REQUIRE(params == "0.00 0.0010.00 10.00");
    }
}

TEST_CASE("DrawingCircleStrategy tests", "[DrawingCircleStrategy]")
{
    auto testCanvas = std::make_shared<TestCanvas>();

    CPoint center{5.0f, 5.0f};
    DrawingCircleStrategy strategy(center, 10.0f);
    Color color("#00FF00");

    SECTION("Draw method calls DrawEllipse")
    {
        testCanvas->Reset();
        strategy.Draw(testCanvas, color);

        REQUIRE(testCanvas->m_setColorCalls == 1);
        REQUIRE(testCanvas->m_drawEllipseCalls == 1);

        REQUIRE(testCanvas->m_lastColor.GetAsUint32() == color.GetAsUint32());
        REQUIRE(testCanvas->m_lastEllipsePosition.x == center.x);
        REQUIRE(testCanvas->m_lastEllipsePosition.y == center.y);
        REQUIRE(testCanvas->m_lastEllipseRx == 10.0f);
        REQUIRE(testCanvas->m_lastEllipseRy == 10.0f);
    }

    SECTION("Constructor throws with negative radius")
    {
        REQUIRE_THROWS_AS(DrawingCircleStrategy(center, -5.0f), std::invalid_argument);
    }

    SECTION("MoveShape updates center")
    {
        CPoint delta{2.0f, 3.0f};
        strategy.MoveShape(delta);

        std::string params = strategy.GetParametersInfoAsString();
        REQUIRE(params.find("7.00") != std::string::npos);
        REQUIRE(params.find("8.00") != std::string::npos);
    }
}

TEST_CASE("DrawingRectangleStrategy tests", "[DrawingRectangleStrategy]")
{
    auto testCanvas = std::make_shared<TestCanvas>();

    CPoint start{0.0f, 0.0f};
    CPoint end{10.0f, 5.0f};
    DrawingRectangleStrategy strategy(start, end);
    Color color("#0000FF");

    SECTION("Draw method draws rectangle with correct points")
    {
        testCanvas->Reset();
        strategy.Draw(testCanvas, color);

        REQUIRE(testCanvas->m_setColorCalls == 1);
        REQUIRE(testCanvas->m_lineToCalls == 4);
        REQUIRE(testCanvas->m_lastColor.GetAsUint32() == color.GetAsUint32());
    }

    SECTION("Get corner points correctly")
    {
        REQUIRE(strategy.GetParametersInfoAsString() == "0.00 0.00 10.00 5.00");
    }
}

TEST_CASE("DrawingPolygonStrategy tests", "[DrawingPolygonStrategy]")
{
    auto testCanvas = std::make_shared<TestCanvas>();

    CPoint center{0.0f, 0.0f};
    DrawingPolygonStrategy strategy(center, 5, 10.0f);
    Color color("#FFFF00");

    SECTION("Constructor validates edges count")
    {
        REQUIRE_THROWS_AS(DrawingPolygonStrategy(center, 2, 10.0f), std::invalid_argument);
    }

    SECTION("Draw method creates polygon vertices")
    {
        testCanvas->Reset();
        strategy.Draw(testCanvas, color);

        REQUIRE(testCanvas->m_setColorCalls == 1);
        REQUIRE(testCanvas->m_moveToCalls == 1);
        REQUIRE(testCanvas->m_lineToCalls == 5);
        REQUIRE(testCanvas->m_lastColor.GetAsUint32() == color.GetAsUint32());
    }
}