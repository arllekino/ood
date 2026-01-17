#pragma once
#include <string>

class Color
{
public:
     explicit Color(const std::string& color);
     [[nodiscard]] uint32_t GetAsUint32() const;
     bool operator==(const Color& other) const;
     friend std::ostream& operator<<(std::ostream& os, const Color& color);
private:
     uint32_t m_color;

     static uint32_t StringToUint32(const std::string& str);
};
