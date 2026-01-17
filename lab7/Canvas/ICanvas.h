#pragma once
#include "../Point/Point.h"
#include "../Color/Color.h"
#include <vector>

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void SetDefaultDrawProperties() = 0;
    virtual void SetFillColor(const Color& color) = 0;
    virtual void SetLineColor(const Color& color) = 0;
    virtual void SetLineWidth(unsigned width) = 0;
    virtual void DrawLine(const Point& from, const Point& to) = 0;
    virtual void DrawEllipse(const Point& center, unsigned width, unsigned height) = 0;
    virtual void DrawPolygon(const std::vector<Point>& points) = 0;
};
