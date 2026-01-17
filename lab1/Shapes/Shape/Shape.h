#pragma once
#include <string>

#include "../CPoint/CPoint.h"
#include "../Color/Color.h"
#include "DrawingStrategy/IDrawingStrategy.h"

struct IDrawingStrategy;
class ICanvas;

namespace shapes
{
    class Shape
    {
    public:
        Shape(std::unique_ptr<IDrawingStrategy> drawingStrategy, std::string id, Color color);

        void MoveShape(const CPoint& deltaPoint) const;
        void Draw(const std::shared_ptr<ICanvas> &canvas) const;
        void SetColor(Color color);
        [[nodiscard]] const Color& GetColor() const;
        void PrintShapeInfo() const;

        [[nodiscard]] std::unique_ptr<Shape> Clone() const;
        [[nodiscard]] const std::string& GetId() const;
    private:
        std::unique_ptr<IDrawingStrategy> m_drawingStrategy;
        std::string m_id;
        Color m_color;

        static const std::string& ConvertShapeTypeToString(shapes::ShapeType type);
    };
}
