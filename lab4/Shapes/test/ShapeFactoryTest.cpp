//
// Created by Miroslav Aktuganov on 18.10.2025.
//
#include <catch2/catch_all.hpp>
#include "../Shape/ShapeFactory/ShapeFactory.h"
#include "../Shape/ShapeType.h"

TEST_CASE("ShapeFactory tests", "[ShapeFactory]")
{
    SECTION("CreateCircle from string stream")
    {
        std::stringstream ss("10.0 20.0 5.0");
        auto shape = ShapeFactory::CreateShape("circle1", Color("#FF0000"), shapes::ShapeType::CIRCLE, ss);

        REQUIRE(shape.GetId() == "circle1");
        REQUIRE(shape.GetColor().GetAsUint32() == 0xFF0000FF);
    }

    SECTION("CreateRectangle from string stream")
    {
        std::stringstream ss("0.0 0.0 10.0 5.0");
        auto shape = ShapeFactory::CreateShape("rect1", Color("#00FF00"), shapes::ShapeType::RECTANGLE, ss);

        REQUIRE(shape.GetId() == "rect1");
    }

    SECTION("CreateLine from string stream")
    {
        std::stringstream ss("0.0 0.0 10.0 10.0");
        auto shape = ShapeFactory::CreateShape("line1", Color("#0000FF"), shapes::ShapeType::LINE, ss);

        REQUIRE(shape.GetId() == "line1");
    }

    SECTION("CreateText from string stream")
    {
        std::stringstream ss("5.0 5.0 12.0 Hello");
        auto shape = ShapeFactory::CreateShape("text1", Color("#FFFF00"), shapes::ShapeType::TEXT, ss);

        REQUIRE(shape.GetId() == "text1");
    }

    SECTION("CreatePolygon from string stream")
    {
        std::stringstream ss("0.0 0.0 10.0 5");
        auto shape = ShapeFactory::CreateShape("poly1", Color("#FF00FF"), shapes::ShapeType::POLYGON, ss);

        REQUIRE(shape.GetId() == "poly1");
    }

    // негативные сценарии
}