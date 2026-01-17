#pragma once

#include <string>

#include "../Color/Color.h"

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void MoveTo(const CPoint& point) = 0;
    virtual void SetColor(const Color& color) = 0;
    virtual void LineTo(const CPoint& point) = 0;
    virtual void DrawEllipse(const CPoint& position, float rx, float ry) = 0;
    virtual void DrawText(const CPoint& position, float fontSize, const std::string& text) = 0;
};
