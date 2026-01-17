#include <catch2/catch_all.hpp>
#include "../Color/Color.h"

TEST_CASE("Color tests")
{
    SECTION("Constructor with valid hex string")
    {
        Color color("#FF0000");
        REQUIRE(color.GetAsUint32() == 0xFF0000FF);
    }

    SECTION("Constructor with different colors")
    {
        Color red("#FF0000");
        Color green("#00FF00");
        Color blue("#0000FF");
        Color white("#FFFFFF");
        Color black("#000000");

        REQUIRE(red.GetAsUint32() == 0xFF0000FF);
        REQUIRE(green.GetAsUint32() == 0x00FF00FF);
        REQUIRE(blue.GetAsUint32() == 0x0000FFFF);
        REQUIRE(white.GetAsUint32() == 0xFFFFFFFF);
        REQUIRE(black.GetAsUint32() == 0x000000FF);
    }

    SECTION("Constructor throws with invalid hex length")
    {
        REQUIRE_THROWS_AS(Color("#FF00"), std::invalid_argument);
        REQUIRE_THROWS_AS(Color("#FF000000"), std::invalid_argument);
        REQUIRE_THROWS_AS(Color(""), std::invalid_argument);
    }

    SECTION("Output stream operator")
    {
        Color color("#AABBCC");
        std::ostringstream os;
        os << std::hex << color;
        REQUIRE(os.str() == "aabbccff");
    }
}