#pragma once
#include "../ShapeType.h"
#include "../../CPoint/CPoint.h"
#include "../../ICanvas/ICanvas.h"
#include "../../Color/Color.h"

// можно по-другому назвать
struct IDrawingStrategy
{
    explicit IDrawingStrategy(const shapes::ShapeType shapeType) : m_shapeType(shapeType) {};
    virtual ~IDrawingStrategy() = default;

    virtual void Draw(std::shared_ptr<ICanvas> canvas, Color color) const = 0;
    virtual void MoveShape(const CPoint& deltaPoint) = 0;

    [[nodiscard]] virtual std::string GetParametersInfoAsString() const = 0;
    [[nodiscard]] shapes::ShapeType GetShapeType() const { return m_shapeType; };
private:
    shapes::ShapeType m_shapeType;
};
