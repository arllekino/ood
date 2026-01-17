#include <SFML/Graphics.hpp>
#include <memory>
#include "./Slide/Slide.h"
#include "./Shapes/Rectangle.h"
#include "./Shapes/Triangle.h"
#include "./Shapes/Ellipse.h"
#include "./Shapes/ShapeGroup.h"
#include "./Canvas/CCanvas.h"

constexpr unsigned g_windowWidth = 800;
constexpr unsigned g_windowHeight = 600;

static std::shared_ptr<Slide> GetSlidesWithShapes()
{
    auto slide = std::make_shared<Slide>();

    auto houseBody = std::make_shared<Rectangle>(Point(300, 300), 200, 150);
    houseBody->SetFillStyle(FillStyle{Color(0xFF6B6BFF)});
    houseBody->SetLineStyle(LineStyle{Color::Black, 2});

    auto roof = std::make_shared<Triangle>(
        Point(250, 300),
        Point(400, 200),
        Point(550, 300)
    );
    roof->SetFillStyle(FillStyle{Color(0x8B4513FF)});
    roof->SetLineStyle(LineStyle{Color::Black, 2});

    auto door = std::make_shared<Rectangle>(Point(350, 380), 40, 70);
    door->SetFillStyle(FillStyle{Color(0x8B4513FF)});

    auto window1 = std::make_shared<Rectangle>(Point(320, 320), 30, 30);
    window1->SetFillStyle(FillStyle{Color::White});
    window1->SetLineStyle(LineStyle{Color::Black, 1});

    auto window2 = std::make_shared<Rectangle>(Point(450, 320), 30, 30);
    window2->SetFillStyle(FillStyle{Color::White});
    window2->SetLineStyle(LineStyle{Color::Black, 1});

    auto sun = std::make_shared<Ellipse>(Point(100, 100), 60, 60);
    sun->SetFillStyle(FillStyle{Color(0xFFFF00FF)});

    auto houseGroup = std::make_shared<ShapeGroup>();
    houseGroup->AddShape(houseBody);
    houseGroup->AddShape(roof);
    houseGroup->AddShape(door);
    houseGroup->AddShape(window1);
    houseGroup->AddShape(window2);

    slide->AddShape(houseGroup);
    slide->AddShape(sun);
    return slide;
}

int main()
{
    auto window = sf::RenderWindow(
        sf::VideoMode({g_windowWidth, g_windowHeight}),
        "Slides",
        sf::State::Windowed,
        sf::ContextSettings(0, 0, 4)
    );
    window.setFramerateLimit(60);

    auto canvas = std::make_unique<Canvas>(window);
    auto slide = GetSlidesWithShapes();

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);

        slide->Draw(*canvas);

        window.display();
    }

    return 0;
}