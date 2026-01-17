#pragma once
#include <SFML/Graphics/Shape.hpp>

#include "../Shape.h"

class ShapeFactory
{
public:
    static shapes::Shape CreateShape(
        const std::string& shapeId,
        Color color,
        shapes::ShapeType type,
        std::stringstream& ss);

private:
    static shapes::Shape CreateCircle(
        const std::string& shapeId,
        Color color,
        std::stringstream& ss);

    static shapes::Shape CreateRectangle(
        const std::string& shapeId,
        Color color,
        std::stringstream& ss);

    static shapes::Shape CreateLine(
        const std::string& shapeId,
        Color color,
        std::stringstream& ss);

    static shapes::Shape CreateText(
        const std::string& shapeId,
        Color color,
        std::stringstream& ss);

    static shapes::Shape CreateTriangle(
        const std::string& shapeId,
        Color color,
        std::stringstream& ss);

    static shapes::Shape CreatePolygon(
        const std::string& shapeId,
        Color color,
        std::stringstream& ss
    );

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

    static shapes::Shape CreatePolygonShapeImpl(
        const std::string& id,
        Color color,
        const CPoint& center,
        float radius,
        unsigned edgesCount);
};
