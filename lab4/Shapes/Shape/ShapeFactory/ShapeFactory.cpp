//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "ShapeFactory.h"

#include "../DrawingStrategy/DrawingCircleStrategy/DrawingCircleStrategy.h"
#include "../DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.h"
#include "../DrawingStrategy/DrawingRectangleStrategy/DrawingRectangleStrategy.h"
#include "../DrawingStrategy/DrawingTextStrategy/DrawingTextStrategy.h"
#include "../DrawingStrategy/DrawingTriangleStrategy/DrawingTriangleStrategy.h"
#include <sstream>

#include "../DrawingStrategy/DrawingPolygonStrategy/DrawingPolygonStrategy.h"

shapes::Shape ShapeFactory::CreateShape(
    const std::string &shapeId,
    const Color color,
    const shapes::ShapeType type,
    std::stringstream &ss)
{
    switch (type)
    {
        case shapes::ShapeType::CIRCLE:
            return CreateCircle(shapeId, color, ss);
        case shapes::ShapeType::RECTANGLE:
            return CreateRectangle(shapeId, color, ss);
        case shapes::ShapeType::LINE:
            return CreateLine(shapeId, color, ss);
        case shapes::ShapeType::TEXT:
            return CreateText(shapeId, color, ss);
        case shapes::ShapeType::TRIANGLE:
            return CreateTriangle(shapeId, color, ss);
        case shapes::ShapeType::POLYGON:
            return CreatePolygon(shapeId, color, ss);
        default:
            assert(false);
    }
}

shapes::Shape ShapeFactory::CreateCircle(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss)
{
    std::string posX, posY, radius;
    ss >> posX >> posY >> radius;
    return CreateCircleImpl(
        shapeId,
        color,
        CPoint(std::stof(posX), std::stof(posY)),
        std::stof(radius)
    );
}

shapes::Shape ShapeFactory::CreateRectangle(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss)
{
    std::string posX, posY, width, height;
    ss >> posX >> posY >> width >> height;
    return CreateRectangleImpl(
        shapeId,
        color,
        CPoint(std::stof(posX), std::stof(posY)),
        std::stof(width),
        std::stof(height)
    );
}

shapes::Shape ShapeFactory::CreateLine(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss)
{
    std::string posX1, posY1, posX2, posY2;
    ss >> posX1 >> posY1 >> posX2 >> posY2;
    return CreateLineImpl(
        shapeId,
        color,
        CPoint(std::stof(posX1), std::stof(posY1)),
        CPoint(std::stof(posX2), std::stof(posY2))
    );
}

shapes::Shape ShapeFactory::CreateText(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss)
{
    std::string posX, posY, fontSizeStr, text;
    ss >> posX >> posY >> fontSizeStr >> text;
    return CreateTextShapeImpl(
        shapeId,
        color,
        CPoint(std::stof(posX), std::stof(posY)),
        std::stof(fontSizeStr),
        text
    );
}

shapes::Shape ShapeFactory::CreateTriangle(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss)
{
    std::string posX1, posY1, posX2, posY2, posX3, posY3;
    ss >> posX1 >> posY1 >> posX2 >> posY2 >> posX3 >> posY3;
    return CreateTriangleImpl(
        shapeId,
        color,
        CPoint(std::stof(posX1), std::stof(posY1)),
        CPoint(std::stof(posX2), std::stof(posY2)),
        CPoint(std::stof(posX3), std::stof(posY3))
    );
}

shapes::Shape ShapeFactory::CreatePolygon(
    const std::string& shapeId,
    const Color color,
    std::stringstream& ss)
{
    std::string posX, posY, radiusStr, edgesCountStr;
    ss >> posX >> posY >> radiusStr >> edgesCountStr;
    return CreatePolygonShapeImpl(
        shapeId,
        color,
        CPoint(std::stof(posX), std::stof(posY)),
        std::stof(radiusStr),
        std::stoi(edgesCountStr));
}


shapes::Shape ShapeFactory::CreateCircleImpl(
    const std::string& id,
    const Color color,
    const CPoint& position,
    float radius)
{
    return {
        std::make_unique<DrawingCircleStrategy>(
        position,
        radius),
        id,
        color};
}

shapes::Shape ShapeFactory::CreateLineImpl(
    const std::string& id,
    const Color color,
    const CPoint& startPosition,
    const CPoint& endPosition)
{
    return {
        std::make_unique<DrawingLineStrategy>(
            startPosition,
            endPosition),
            id, color};
}

shapes::Shape ShapeFactory::CreateRectangleImpl(
    const std::string& id,
    const Color color,
    const CPoint& startPosition,
    const float width,
    const float height)
{
    return {
        std::make_unique<DrawingRectangleStrategy>(
            startPosition,
            CPoint(startPosition.x + width, startPosition.y + height)),
            id,
            color
        };
}

shapes::Shape ShapeFactory::CreateTriangleImpl(
    const std::string& id,
    const Color color,
    const CPoint& vertex1,
    const CPoint& vertex2,
    const CPoint& vertex3)
{
    return {
        std::make_unique<DrawingTriangleStrategy>(
            vertex1,
            vertex2,
            vertex3),
        id,
        color};
}

shapes::Shape ShapeFactory::CreateTextShapeImpl(
    const std::string& id,
    const Color color,
    const CPoint& position,
    const float fontSize,
    const std::string& text)
{
    return {
       std::make_unique<DrawingTextStrategy>(
           text,
           fontSize,
           position),
       id,
       color};
}

shapes::Shape ShapeFactory::CreatePolygonShapeImpl(
    const std::string& id,
    const Color color,
    const CPoint& center,
    const float radius,
    unsigned edgesCount)
{
    return {
        std::make_unique<DrawingPolygonStrategy>(
            center,
            edgesCount,
            radius),
        id,
        color};
}
