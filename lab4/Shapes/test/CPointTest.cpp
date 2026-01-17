//
// Created by Miroslav Aktuganov on 18.10.2025.
//

#include <catch2/catch_all.hpp>
#include "../CPoint/CPoint.h"

TEST_CASE("CPoint struct tests")
{
    SECTION("Default constructor")
    {
        CPoint point;
        REQUIRE(point.x == 0.0f);
        REQUIRE(point.y == 0.0f);
    }

    SECTION("Equality operator")
    {
        CPoint p1{1.0f, 2.0f};
        CPoint p2{1.0f, 2.0f};
        CPoint p3{1.5f, 2.0f};
        CPoint p4{1.0f, 2.5f};

        REQUIRE(p1 == p2);
        REQUIRE_FALSE(p1 == p3);
        REQUIRE_FALSE(p1 == p4);
    }

    SECTION("Addition operator")
    {
        CPoint p1{1.0f, 2.0f};
        CPoint p2{3.0f, 4.0f};
        CPoint result = p1 + p2;

        REQUIRE(result.x == 4.0f);
        REQUIRE(result.y == 6.0f);
    }

    SECTION("Compound addition operator")
    {
        CPoint p1{1.0f, 2.0f};
        CPoint p2{3.0f, 4.0f};
        p1 += p2;

        REQUIRE(p1.x == 4.0f);
        REQUIRE(p1.y == 6.0f);
    }
}