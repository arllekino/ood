//
// Created by Miroslav Aktuganov on 12.09.2025.
//

#include "ShapeType.h"
#include "Shape.h"

#include <assert.h>
#include <iomanip>
#include <iostream>

namespace shapes
{
    Shape::Shape(
        std::unique_ptr<IDrawingStrategy> drawingStrategy,
        std::string id,
        const Color color)
            : m_drawingStrategy(std::move(drawingStrategy)),
            m_id(std::move(id)),
            m_color(color)
    {
    }

    void Shape::MoveShape(const CPoint &deltaPoint) const
    {
        m_drawingStrategy->MoveShape(deltaPoint);
    }

    void Shape::Draw(const std::shared_ptr<ICanvas> &canvas) const
    {
        m_drawingStrategy->Draw(canvas, m_color);
    }

    void Shape::SetColor(const Color color)
    {
        m_color = color;
    }

    const Color & Shape::GetColor() const
    {
        return m_color;
    }

    void Shape::PrintShapeInfo() const
    {
        std::cout
            << ConvertShapeTypeToString(m_drawingStrategy->GetShapeType())
            << m_id
            << std::uppercase << std::hex << std::setw(6) << std::setfill('0')
            << (m_color.GetAsUint32() & 0xFFFFFF)
            << std::dec
            << m_drawingStrategy->GetParametersInfoAsString()
            << std::endl;
    }

    std::unique_ptr<Shape> Shape::Clone() const
    {
        // TODO
        assert(false);
        return nullptr;
    }

    const std::string & Shape::GetId() const
    {
        return m_id;
    }

    const std::string& Shape::ConvertShapeTypeToString(const shapes::ShapeType type)
    {
        switch (type)
        {
            case shapes::ShapeType::CIRCLE:
                return "circle";
            case shapes::ShapeType::RECTANGLE:
                return "rectangle";
            case shapes::ShapeType::TRIANGLE:
                return "triangle";
            case shapes::ShapeType::LINE:
                return "line";
            case shapes::ShapeType::TEXT:
                return "text";
            default:
                assert(false);
        }
    }
}
