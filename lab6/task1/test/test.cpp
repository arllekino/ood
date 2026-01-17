#include <catch2/catch_all.hpp>
#include <sstream>
#include <iostream>

#include "../Adapter/ModernGraphicsClassAdapter.h"
#include "../graphics_lib/graphics_lib.h"
#include "../modern_graphics_lib/modern_graphics_lib.h"
#include "../shape_drawing_lib/shape_drawing_lib.h"
#include "../Adapter/ModernGraphicsLibAdapter.h"

constexpr uint32_t COLOR_BLACK = 0x00000000;
constexpr uint32_t COLOR_WHITE = 0xffffff00;
constexpr uint32_t COLOR_RED   = 0xff000000;
constexpr uint32_t COLOR_GREEN = 0x00ff0000;
constexpr uint32_t COLOR_BLUE  = 0x0000ff00;

constexpr uint32_t COLOR_TEXT_DEFAULT = 0x32353700;

TEST_CASE("GraphicsLib Canvas basic operations")
{
    std::stringstream output;
    
    auto oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    graphics_lib::CCanvas canvas;
    canvas.MoveTo(10, 20);
    canvas.LineTo(30, 40);
    canvas.MoveTo(50, 60);
    canvas.LineTo(70, 80);

    std::cout.rdbuf(oldCoutBuf);
    
    std::string expected = 
        "MoveTo (10, 20)\n"
        "LineTo (30, 40)\n"
        "MoveTo (50, 60)\n"
        "LineTo (70, 80)\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("ModernGraphicsLib Renderer basic operations") {
    std::stringstream output;
    
    modern_graphics_lib::CModernGraphicsRenderer renderer(output);
    
    renderer.BeginDraw();
    renderer.DrawLine({10, 20}, {30, 40}, {0, 0, 0, 0});
    renderer.DrawLine({50, 60}, {70, 80}, {0.02, 0.04, 0.25, 0});
    renderer.EndDraw();
    
    std::string expected = 
        "<draw>\n"
        "  <line fromX=\"10\" fromY=\"20\" toX=\"30\" toY=\"40\">\n"
        "    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"50\" fromY=\"60\" toX=\"70\" toY=\"80\">\n"
        "    <color r=\"0.02\" g=\"0.04\" b=\"0.25\" a=\"0\" />\n"
        "  </line>\n"
        "</draw>\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("ModernGraphicsLib Renderer exception handling")
{
    std::stringstream output;
    modern_graphics_lib::CModernGraphicsRenderer renderer(output);
    
    SECTION("DrawLine without BeginDraw should throw")
    {
        REQUIRE_THROWS_AS(
            renderer.DrawLine({10, 20}, {30, 40}, {0.02, 0.04, 0.25, 0}),
            std::logic_error
        );
    }
    
    SECTION("Double BeginDraw should throw")
    {
        renderer.BeginDraw();
        REQUIRE_THROWS_AS(renderer.BeginDraw(), std::logic_error);
        renderer.EndDraw();
    }
    
    SECTION("EndDraw without BeginDraw should throw")
    {
        REQUIRE_THROWS_AS(renderer.EndDraw(), std::logic_error);
    }
}

TEST_CASE("ShapeDrawingLib Triangle drawing")
{
    std::stringstream output;
    auto oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    graphics_lib::CCanvas canvas;
    shape_drawing_lib::CTriangle triangle({10, 15}, {100, 200}, {150, 250}, COLOR_RED);
    triangle.Draw(canvas);

    std::cout.rdbuf(oldCoutBuf);
    
    std::string expected =
        "#ff0000\n"
        "MoveTo (10, 15)\n"
        "LineTo (100, 200)\n"
        "LineTo (150, 250)\n"
        "LineTo (10, 15)\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("ShapeDrawingLib Rectangle drawing")
{
    std::stringstream output;
    auto oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    graphics_lib::CCanvas canvas;
    shape_drawing_lib::CRectangle rectangle({30, 40}, 18, 24, COLOR_RED);
    rectangle.Draw(canvas);

    std::cout.rdbuf(oldCoutBuf);
    
    std::string expected =
        "#ff0000\n"
        "MoveTo (30, 40)\n"
        "LineTo (48, 40)\n"
        "LineTo (48, 64)\n"
        "LineTo (30, 64)\n"
        "LineTo (30, 40)\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("ModernGraphicsLib Adapter basic operations")
{
    std::stringstream output;
    {
        modern_graphics_lib::CModernGraphicsRenderer renderer(output);
        app::ModernGraphicsLibAdapter adapter(renderer);

        adapter.MoveTo(10, 20);
        adapter.LineTo(30, 40);
        adapter.LineTo(50, 60);
    }
    std::string expected =
        "<draw>\n"
        "  <line fromX=\"10\" fromY=\"20\" toX=\"30\" toY=\"40\">\n"
        "    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"30\" fromY=\"40\" toX=\"50\" toY=\"60\">\n"
        "    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "</draw>\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("ModernGraphicsLib Adapter multiple MoveTo operations")
{
    std::stringstream output;
    {
        modern_graphics_lib::CModernGraphicsRenderer renderer(output);
        app::ModernGraphicsLibAdapter adapter(renderer);

        adapter.MoveTo(10, 20);
        adapter.LineTo(30, 40);
        adapter.MoveTo(50, 60);
        adapter.LineTo(70, 80);
    }
    std::string expected = 
        "<draw>\n"
        "  <line fromX=\"10\" fromY=\"20\" toX=\"30\" toY=\"40\">\n"
        "    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"50\" fromY=\"60\" toX=\"70\" toY=\"80\">\n"
        "    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "</draw>\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("CanvasPainter with ModernGraphicsLib Adapter")
{
    std::stringstream output;
    {
        modern_graphics_lib::CModernGraphicsRenderer renderer(output);
        app::ModernGraphicsLibAdapter adapter(renderer);
        shape_drawing_lib::CCanvasPainter painter(adapter);

        shape_drawing_lib::CTriangle triangle({10, 15}, {100, 200}, {150, 250}, COLOR_TEXT_DEFAULT);
        painter.Draw(triangle);
    }
    std::string expected = 
        "<draw>\n"
        "  <line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\">\n"
        "    <color r=\"0.196078\" g=\"0.207843\" b=\"0.215686\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\">\n"
        "    <color r=\"0.196078\" g=\"0.207843\" b=\"0.215686\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\">\n"
        "    <color r=\"0.196078\" g=\"0.207843\" b=\"0.215686\" a=\"0\" />\n"
        "  </line>\n"
        "</draw>\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("Full PaintPicture integration with ModernGraphicsLib")
{
    std::stringstream output;
    {
        modern_graphics_lib::CModernGraphicsRenderer renderer(output);
        app::ModernGraphicsLibAdapter adapter(renderer);
        shape_drawing_lib::CCanvasPainter painter(adapter);

        auto PaintPicture = [](const shape_drawing_lib::CCanvasPainter& painter) {
            using namespace shape_drawing_lib;
            CTriangle triangle({10, 15}, {100, 200}, {150, 250}, COLOR_GREEN);
            CRectangle rectangle({30, 40}, 18, 24, COLOR_BLUE);
            painter.Draw(triangle);
            painter.Draw(rectangle);
        };

        PaintPicture(painter);
    }
    std::string expected = 
        "<draw>\n"
        "  <line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\">\n"
        "    <color r=\"0\" g=\"1\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\">\n"
        "    <color r=\"0\" g=\"1\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\">\n"
        "    <color r=\"0\" g=\"1\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"30\" fromY=\"40\" toX=\"48\" toY=\"40\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"48\" fromY=\"40\" toX=\"48\" toY=\"64\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"48\" fromY=\"64\" toX=\"30\" toY=\"64\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"30\" fromY=\"64\" toX=\"30\" toY=\"40\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "</draw>\n";
    
    REQUIRE(output.str() == expected);
}

TEST_CASE("ModernGraphicsClassAdapter")
{
    std::stringstream output;
    {
        ModernGraphicsClassAdapter adapter(output);
        shape_drawing_lib::CCanvasPainter painter(adapter);

        auto PaintPicture = [](const shape_drawing_lib::CCanvasPainter& painter) {
            using namespace shape_drawing_lib;
            CTriangle triangle({10, 15}, {100, 200}, {150, 250}, COLOR_GREEN);
            CRectangle rectangle({30, 40}, 18, 24, COLOR_BLUE);
            painter.Draw(triangle);
            painter.Draw(rectangle);
        };
        PaintPicture(painter);
    }
    std::string expected =
        "<draw>\n"
        "  <line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\">\n"
        "    <color r=\"0\" g=\"1\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\">\n"
        "    <color r=\"0\" g=\"1\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\">\n"
        "    <color r=\"0\" g=\"1\" b=\"0\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"30\" fromY=\"40\" toX=\"48\" toY=\"40\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"48\" fromY=\"40\" toX=\"48\" toY=\"64\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"48\" fromY=\"64\" toX=\"30\" toY=\"64\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "  <line fromX=\"30\" fromY=\"64\" toX=\"30\" toY=\"40\">\n"
        "    <color r=\"0\" g=\"0\" b=\"1\" a=\"0\" />\n"
        "  </line>\n"
        "</draw>\n";

    REQUIRE(output.str() == expected);
}