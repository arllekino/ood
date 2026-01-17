#include <catch2/catch_all.hpp>
#include "../Shapes/Rectangle.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/Ellipse.h"
#include "../Shapes/ShapeGroup.h"
#include "../Color/Color.h"

TEST_CASE("ShapeGroup basic functionality")
{
    SECTION("Empty group has zero border rect")
    {
        ShapeGroup group;
        auto borderRect = group.GetBorderRect();
        
        REQUIRE(borderRect.GetLeftTop().x == 0);
        REQUIRE(borderRect.GetLeftTop().y == 0);
        REQUIRE(borderRect.GetWidth() == 0);
        REQUIRE(borderRect.GetHeight() == 0);
    }

    SECTION("Group with single shape has same border rect as the shape")
    {
        auto rect = std::make_shared<Rectangle>(Point(10, 20), 100, 50);
        ShapeGroup group;
        group.AddShape(rect);
        
        auto groupBorder = group.GetBorderRect();
        auto rectBorder = rect->GetBorderRect();
        
        REQUIRE(groupBorder.GetLeftTop().x == rectBorder.GetLeftTop().x);
        REQUIRE(groupBorder.GetLeftTop().y == rectBorder.GetLeftTop().y);
        REQUIRE(groupBorder.GetWidth() == rectBorder.GetWidth());
        REQUIRE(groupBorder.GetHeight() == rectBorder.GetHeight());
    }

    SECTION("Group calculates correct border rect for multiple shapes")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 20), 100, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(50, 30), 80, 60);
        auto ellipse = std::make_shared<Ellipse>(Point(200, 100), 40, 40);
        
        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);
        group.AddShape(ellipse);
        
        auto borderRect = group.GetBorderRect();
        
        REQUIRE(borderRect.GetLeftTop().x == 10);
        REQUIRE(borderRect.GetLeftTop().y == 20);
        REQUIRE(borderRect.GetWidth() == 210);
        REQUIRE(borderRect.GetHeight() == 100);
    }

    SECTION("Setting line style applies to all shapes in group")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 10), 50, 50);

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        LineStyle lineStyle{Color::Red, 3};
        group.SetLineStyle(lineStyle);

        REQUIRE(rect1->GetLineStyle().has_value());
        REQUIRE(rect1->GetLineStyle()->color == Color::Red);
        REQUIRE(rect1->GetLineStyle()->width == 3);

        REQUIRE(rect2->GetLineStyle().has_value());
        REQUIRE(rect2->GetLineStyle()->color == Color::Red);
        REQUIRE(rect2->GetLineStyle()->width == 3);
    }

    SECTION("Setting fill style applies to all shapes in group")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 10), 50, 50);

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        FillStyle fillStyle{Color::Blue};
        group.SetFillStyle(fillStyle);

        REQUIRE(rect1->GetFillStyle().has_value());
        REQUIRE(rect1->GetFillStyle()->color == Color::Blue);

        REQUIRE(rect2->GetFillStyle().has_value());
        REQUIRE(rect2->GetFillStyle()->color == Color::Blue);
    }

    SECTION("Getting line style returns common style when all shapes have same")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 10), 50, 50);

        LineStyle commonStyle{Color::Green, 2};
        rect1->SetLineStyle(commonStyle);
        rect2->SetLineStyle(commonStyle);

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        auto groupLineStyle = group.GetLineStyle();
        REQUIRE(groupLineStyle.has_value());
        REQUIRE(groupLineStyle->color == Color::Green);
        REQUIRE(groupLineStyle->width == 2);
    }

    SECTION("Getting line style returns nullopt when shapes have different styles")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 10), 50, 50);

        rect1->SetLineStyle(LineStyle{Color::Red, 1});
        rect2->SetLineStyle(LineStyle{Color::Blue, 2});

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        auto groupLineStyle = group.GetLineStyle();
        REQUIRE_FALSE(groupLineStyle.has_value());
    }

    SECTION("Getting fill style returns common style when all shapes have same")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 10), 50, 50);

        FillStyle commonStyle{Color::Yellow};
        rect1->SetFillStyle(commonStyle);
        rect2->SetFillStyle(commonStyle);

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        auto groupFillStyle = group.GetFillStyle();
        REQUIRE(groupFillStyle.has_value());
        REQUIRE(groupFillStyle->color == Color::Yellow);
    }

    SECTION("Getting fill style returns nullopt when shapes have different styles")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 10), 50, 50);

        rect1->SetFillStyle(FillStyle{Color::Red});
        rect2->SetFillStyle(FillStyle{Color::Blue});

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        auto groupFillStyle = group.GetFillStyle();
        REQUIRE_FALSE(groupFillStyle.has_value());
    }

    SECTION("Setting border rect scales shapes proportionally")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 70), 30, 30);

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        auto originalBorder = group.GetBorderRect();

        BorderRectangle newBorder{
            Point(originalBorder.GetLeftTop().x, originalBorder.GetLeftTop().y),
            originalBorder.GetWidth() * 2,
            originalBorder.GetHeight() * 2
        };

        group.SetBorderRect(newBorder);

        auto rect1NewBorder = rect1->GetBorderRect();
        auto rect2NewBorder = rect2->GetBorderRect();

        REQUIRE(rect1NewBorder.GetWidth() == 100);
        REQUIRE(rect1NewBorder.GetHeight() == 100);
        REQUIRE(rect2NewBorder.GetWidth() == 60);
        REQUIRE(rect2NewBorder.GetHeight() == 60);
    }

    SECTION("Group handles shapes with no styles correctly")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto rect2 = std::make_shared<Rectangle>(Point(70, 10), 50, 50);

        rect1->SetFillStyle(FillStyle{Color::Red});
        rect1->SetLineStyle(LineStyle{Color::Black, 1});

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        REQUIRE_FALSE(group.GetFillStyle().has_value());
        REQUIRE_FALSE(group.GetLineStyle().has_value());

        group.SetFillStyle(FillStyle{Color::Blue});
        group.SetLineStyle(LineStyle{Color::White, 2});

        REQUIRE(rect1->GetFillStyle()->color == Color::Blue);
        REQUIRE(rect2->GetFillStyle()->color == Color::Blue);
        REQUIRE(rect1->GetLineStyle()->color == Color::White);
        REQUIRE(rect2->GetLineStyle()->color == Color::White);
    }
}

TEST_CASE("Clone functionality")
{
    SECTION("Rectangle clone creates independent copy")
    {
        auto original = std::make_shared<Rectangle>(Point(10, 20), 100, 50);
        original->SetFillStyle(FillStyle{Color::Red});
        original->SetLineStyle(LineStyle{Color::Blue, 2});

        auto clone = original->Clone();

        REQUIRE(clone->GetBorderRect().GetLeftTop().x == 10);
        REQUIRE(clone->GetBorderRect().GetLeftTop().y == 20);
        REQUIRE(clone->GetBorderRect().GetWidth() == 100);
        REQUIRE(clone->GetBorderRect().GetHeight() == 50);

        auto cloneFillStyle = clone->GetFillStyle();
        REQUIRE(cloneFillStyle.has_value());
        REQUIRE(cloneFillStyle->color == Color::Red);

        auto cloneLineStyle = clone->GetLineStyle();
        REQUIRE(cloneLineStyle.has_value());
        REQUIRE(cloneLineStyle->color == Color::Blue);
        REQUIRE(cloneLineStyle->width == 2);

        original->SetBorderRect(BorderRectangle{Point(30, 40), 150, 75});
        original->SetFillStyle(FillStyle{Color::Green});

        REQUIRE(clone->GetBorderRect().GetLeftTop().x == 10);
        REQUIRE(clone->GetBorderRect().GetLeftTop().y == 20);
        REQUIRE(clone->GetFillStyle()->color == Color::Red);
    }

    SECTION("Triangle clone creates independent copy")
    {
        auto original = std::make_shared<Triangle>(
            Point(10, 10), Point(50, 10), Point(30, 40)
        );
        original->SetFillStyle(FillStyle{Color::Magenta});

        auto clone = original->Clone();

        auto originalFill = original->GetFillStyle();
        auto cloneFill = clone->GetFillStyle();

        REQUIRE(originalFill.has_value());
        REQUIRE(cloneFill.has_value());
        REQUIRE(originalFill->color == Color::Magenta);
        REQUIRE(cloneFill->color == Color::Magenta);

        original->SetFillStyle(FillStyle{Color::Cyan});

        REQUIRE(clone->GetFillStyle()->color == Color::Magenta);
    }

    SECTION("Ellipse clone creates independent copy")
    {
        auto original = std::make_shared<Ellipse>(Point(100, 100), 80, 60);
        original->SetLineStyle(LineStyle{Color::Yellow, 3});

        auto clone = original->Clone();

        auto originalBorder = original->GetBorderRect();
        auto cloneBorder = clone->GetBorderRect();

        REQUIRE(originalBorder.GetLeftTop().x == 60);
        REQUIRE(originalBorder.GetLeftTop().y == 70);
        REQUIRE(originalBorder.GetWidth() == 80);
        REQUIRE(originalBorder.GetHeight() == 60);

        REQUIRE(originalBorder.GetLeftTop().x == cloneBorder.GetLeftTop().x);
        REQUIRE(originalBorder.GetLeftTop().y == cloneBorder.GetLeftTop().y);
        REQUIRE(originalBorder.GetWidth() == cloneBorder.GetWidth());
        REQUIRE(originalBorder.GetHeight() == cloneBorder.GetHeight());

        original->SetBorderRect(BorderRectangle{Point(50, 50), 40, 30});

        REQUIRE(cloneBorder.GetLeftTop().x == 60);
        REQUIRE(cloneBorder.GetLeftTop().y == 70);
        REQUIRE(cloneBorder.GetWidth() == 80);
        REQUIRE(cloneBorder.GetHeight() == 60);
    }

    SECTION("ShapeGroup clone creates deep copy with independent shapes")
    {
        auto rect = std::make_shared<Rectangle>(Point(10, 10), 50, 50);
        auto triangle = std::make_shared<Triangle>(
            Point(70, 10), Point(90, 10), Point(80, 30)
        );

        auto originalGroup = std::make_shared<ShapeGroup>();
        originalGroup->AddShape(rect);
        originalGroup->AddShape(triangle);

        originalGroup->SetFillStyle(FillStyle{Color::Red});
        originalGroup->SetLineStyle(LineStyle{Color::Black, 1});

        auto clonedGroup = originalGroup->Clone();

        auto originalBorder = originalGroup->GetBorderRect();
        auto clonedBorder = clonedGroup->GetBorderRect();

        REQUIRE(originalBorder.GetLeftTop().x == clonedBorder.GetLeftTop().x);
        REQUIRE(originalBorder.GetLeftTop().y == clonedBorder.GetLeftTop().y);
        REQUIRE(originalBorder.GetWidth() == clonedBorder.GetWidth());
        REQUIRE(originalBorder.GetHeight() == clonedBorder.GetHeight());

        originalGroup->SetFillStyle(FillStyle{Color::Blue});
        originalGroup->SetLineStyle(LineStyle{Color::White, 2});

        auto clonedFill = clonedGroup->GetFillStyle();
        auto clonedLine = clonedGroup->GetLineStyle();

        REQUIRE(clonedFill.has_value());
        REQUIRE(clonedFill->color == Color::Red);

        REQUIRE(clonedLine.has_value());
        REQUIRE(clonedLine->color == Color::Black);
        REQUIRE(clonedLine->width == 1);
    }

    SECTION("Nested group clone works correctly")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 30, 30);
        auto rect2 = std::make_shared<Rectangle>(Point(50, 10), 30, 30);

        auto innerGroup = std::make_shared<ShapeGroup>();
        innerGroup->AddShape(rect1);
        innerGroup->AddShape(rect2);

        auto outerGroup = std::make_shared<ShapeGroup>();
        outerGroup->AddShape(innerGroup);

        auto clonedOuterGroup = outerGroup->Clone();

        outerGroup->SetFillStyle(FillStyle{Color::Green});

        auto clonedFill = clonedOuterGroup->GetFillStyle();
        REQUIRE_FALSE(clonedFill.has_value());
    }

    SECTION("Clone maintains correct relationships in groups")
    {
        auto shape1 = std::make_shared<Rectangle>(Point(0, 0), 100, 100);
        auto shape2 = std::make_shared<Ellipse>(Point(150, 150), 50, 50);

        auto group = std::make_shared<ShapeGroup>();
        group->AddShape(shape1);
        group->AddShape(shape2);

        auto clonedGroup = group->Clone();

        auto originalBorder = group->GetBorderRect();
        BorderRectangle newBorder{
            Point(originalBorder.GetLeftTop().x, originalBorder.GetLeftTop().y),
            originalBorder.GetWidth() * 2,
            originalBorder.GetHeight() * 2
        };
        group->SetBorderRect(newBorder);

        auto clonedBorder = clonedGroup->GetBorderRect();
        REQUIRE(clonedBorder.GetWidth() == originalBorder.GetWidth());
        REQUIRE(clonedBorder.GetHeight() == originalBorder.GetHeight());
    }

    SECTION("Clone of empty group works")
    {
        auto emptyGroup = std::make_shared<ShapeGroup>();
        auto clonedEmptyGroup = emptyGroup->Clone();

        REQUIRE(clonedEmptyGroup->GetBorderRect().GetWidth() == 0);
        REQUIRE(clonedEmptyGroup->GetBorderRect().GetHeight() == 0);
        REQUIRE_FALSE(clonedEmptyGroup->GetFillStyle().has_value());
        REQUIRE_FALSE(clonedEmptyGroup->GetLineStyle().has_value());
    }
}

TEST_CASE("Complex ShapeGroup scenarios")
{
    SECTION("Group with mixed shape types")
    {
        auto rect = std::make_shared<Rectangle>(Point(10, 10), 100, 50);
        auto triangle = std::make_shared<Triangle>(
            Point(120, 10), Point(170, 10), Point(145, 40)
        );
        auto ellipse = std::make_shared<Ellipse>(Point(200, 35), 60, 30);

        ShapeGroup group;
        group.AddShape(rect);
        group.AddShape(triangle);
        group.AddShape(ellipse);

        auto border = group.GetBorderRect();
        REQUIRE(border.GetLeftTop().x == 10);
        REQUIRE(border.GetLeftTop().y == 10);
        REQUIRE(border.GetWidth() == 220);
        REQUIRE(border.GetHeight() == 50);

        group.SetFillStyle(FillStyle{Color::Cyan});

        REQUIRE(rect->GetFillStyle()->color == Color::Cyan);
        REQUIRE(triangle->GetFillStyle()->color == Color::Cyan);
        REQUIRE(ellipse->GetFillStyle()->color == Color::Cyan);
    }

    SECTION("Multiple levels of grouping")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 40, 40);
        auto rect2 = std::make_shared<Rectangle>(Point(60, 10), 40, 40);
        auto rect3 = std::make_shared<Rectangle>(Point(110, 10), 40, 40);

        auto group1 = std::make_shared<ShapeGroup>();
        group1->AddShape(rect1);
        group1->AddShape(rect2);

        auto group2 = std::make_shared<ShapeGroup>();
        group2->AddShape(group1);
        group2->AddShape(rect3);

        auto border = group2->GetBorderRect();
        REQUIRE(border.GetLeftTop().x == 10);
        REQUIRE(border.GetLeftTop().y == 10);
        REQUIRE(border.GetWidth() == 140);
        REQUIRE(border.GetHeight() == 40);

        auto clonedGroup = group2->Clone();
        auto clonedBorder = clonedGroup->GetBorderRect();

        REQUIRE(border.GetLeftTop().x == clonedBorder.GetLeftTop().x);
        REQUIRE(border.GetLeftTop().y == clonedBorder.GetLeftTop().y);
        REQUIRE(border.GetWidth() == clonedBorder.GetWidth());
        REQUIRE(border.GetHeight() == clonedBorder.GetHeight());
    }

    SECTION("Group transformation preserves relative positions")
    {
        auto rect1 = std::make_shared<Rectangle>(Point(10, 10), 20, 20);
        auto rect2 = std::make_shared<Rectangle>(Point(40, 40), 20, 20);

        ShapeGroup group;
        group.AddShape(rect1);
        group.AddShape(rect2);

        auto originalBorder = group.GetBorderRect();

        BorderRectangle newBorder{
            Point(50, 50),
            originalBorder.GetWidth() * 2,
            originalBorder.GetHeight() * 2
        };
        group.SetBorderRect(newBorder);

        auto rect1NewBorder = rect1->GetBorderRect();
        auto rect2NewBorder = rect2->GetBorderRect();

        REQUIRE(rect2NewBorder.GetLeftTop().x - rect1NewBorder.GetLeftTop().x == 60);
        REQUIRE(rect2NewBorder.GetLeftTop().y - rect1NewBorder.GetLeftTop().y == 60);
    }
}