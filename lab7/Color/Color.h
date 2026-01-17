#pragma once

class Color
{
public:
    explicit Color(const uint32_t color)
        : m_color(color) {};

    explicit Color(const std::string& color)
        : m_color(ConvertStringToUint32(color)) {};

    [[nodiscard]] uint32_t GetAsUint32() const
    {
        return m_color;
    }

    bool operator==(const Color& rhs) const
    {
        return m_color == rhs.m_color;
    }

    static const Color White;
    static const Color Black;
    static const Color Clear;
    static const Color Red;
    static const Color Blue;
    static const Color Green;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
private:
    uint32_t m_color;

    static uint32_t ConvertStringToUint32(const std::string& color)
    {
        if (color.at(0) != '#' || color.length() != 9)
        {
            throw std::invalid_argument("Invalid color format. Expected '#RRGGBBAA'.");
        }

        std::string hexStr = color.substr(1, 8);
        return static_cast<uint32_t>(std::stoul(hexStr, nullptr, 16));
    }
};

const Color Color::Clear = Color(0x00000000);
const Color Color::Black = Color(0x000000FF);
const Color Color::White = Color(0xFFFFFFFF);
const Color Color::Red = Color(0xFF0000FF);
const Color Color::Blue = Color(0x00FF0000);
const Color Color::Green = Color(0x00FF00FF);
const Color Color::Yellow = Color(0xFFFF00FF);
const Color Color::Magenta = Color(0xFF00FFFF);
const Color Color::Cyan = Color(0x00FFFFFF);