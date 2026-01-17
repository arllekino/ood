#pragma once
#include <string>

class Color
{
public:
     explicit Color(const std::string& color);
     uint32_t GetAsUint32() const;
     friend std::ostream& operator<<(std::ostream& os, const Color& color);
private:
     uint32_t m_color;

     static uint32_t StringToUint32(const std::string& str);
};
