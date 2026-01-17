#pragma once
#include "../Shape.h"

class ShapeFactory
{
public:
    static shapes::Shape CreateCircleImpl(
        const std::string& id,
        Color color,
        const CPoint& position,
        float radius);

    static shapes::Shape CreateLineImpl(
        const std::string& id,
        Color color,
        const CPoint& startPosition,
        const CPoint& endPosition);

    static shapes::Shape CreateRectangleImpl(
        const std::string& id,
        Color color,
        const CPoint& startPosition,
        float width,
        float height);

    static shapes::Shape CreateTriangleImpl(
        const std::string& id,
        Color color,
        const CPoint& vertex1,
        const CPoint& vertex2,
        const CPoint& vertex3);

    static shapes::Shape CreateTextShapeImpl(
        const std::string& id,
        Color color,
        const CPoint& position,
        float fontSize,
        const std::string& text);
};
