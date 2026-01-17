#include <iostream>

#include "ShapesController/ShapesController.h"

constexpr unsigned g_windowWidth = 800;
constexpr unsigned g_windowHeight = 600;

int main()
{
    auto window = sf::RenderWindow(
        sf::VideoMode({g_windowWidth, g_windowHeight}),
        "Shapes visualization",
        sf::State::Windowed,
        sf::ContextSettings(0, 0, 4)
    );;
    auto shapesController = ShapesController(window);

    window.display();

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        while (!std::cin.eof())
        {
            shapesController.OnInput(std::cin);
        }

        window.clear(sf::Color::White);
        shapesController.DrawPicture();
        window.display();
    }

    return 0;
}