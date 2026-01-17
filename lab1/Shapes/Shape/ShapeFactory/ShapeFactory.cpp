//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "ShapeFactory.h"

#include "../DrawingStrategy/DrawingCircleStrategy/DrawingCircleStrategy.h"
#include "../DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.h"
#include "../DrawingStrategy/DrawingRectangleStrategy/DrawingRectangleStrategy.h"
#include "../DrawingStrategy/DrawingTextStrategy/DrawingTextStrategy.h"
#include "../DrawingStrategy/DrawingTriangleStrategy/DrawingTriangleStrategy.h"

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
