//
// Created by Miroslav Aktuganov on 14.09.2025.
//

#include "Color.h"

#include <iostream>
#include <SFML/Graphics.hpp>

Color::Color(const std::string& color)
    : m_color(StringToUint32(color))
{
}

uint32_t Color::GetAsUint32() const
{
    return m_color;
}

bool Color::operator==(const Color& other) const
{
    return m_color == other.m_color;
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
    os << color.m_color;
    return os;
}

uint32_t Color::StringToUint32(const std::string& str)
{
    if (str.length() != 7)
    {
        throw std::invalid_argument("Invalid color format. Expected HEX string like this '#FFFFFF' .");
    }

    const uint32_t color = std::stoul(str.substr(1), nullptr, 16);

    const uint8_t r = (color >> 16) & 0xFF;
    const uint8_t g = (color >> 8) & 0xFF;
    const uint8_t b = color & 0xFF;

    return sf::Color(r, g, b).toInteger();
}
