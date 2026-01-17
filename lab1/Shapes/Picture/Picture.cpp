//
// Created by Miroslav Aktuganov on 13.09.2025.
//

#include "Picture.h"

#include "../CCanvas/CCanvas.h"

Picture::Picture(sf::RenderWindow& window)
{
    m_canvas = std::make_shared<CCanvas>(window);
}

void Picture::AddShape(std::shared_ptr<shapes::Shape> shape)
{
    m_shapes.insert({ shape->GetId(), shape });
}

void Picture::DrawShape(const std::string& shapeId)
{
    AssertShapeExist(shapeId);
    auto shape = m_shapes.at(shapeId);
    m_shapesToDraw.insert({ shapeId, shape });
}

void Picture::DrawShapes()
{
    for (auto shape : m_shapes)
    {
        m_shapesToDraw.insert(shape);
    }
}

void Picture::DrawPicture() const
{
    for (const auto [id, shape] : m_shapesToDraw)
    {
        shape->Draw(m_canvas);
    }
}

void Picture::MoveShape(const std::string& shapeId, const CPoint& deltaPoint) const
{
    m_shapes.at(shapeId)->MoveShape(deltaPoint);
}

void Picture::MovePicture(const CPoint& deltaPoint)
{
    for (const auto [id, shape] : m_shapes)
        {
        shape->MoveShape(deltaPoint);
    }
}

void Picture::DeleteShape(const std::string& shapeId)
{
    m_shapes.erase(shapeId);
}

void Picture::List() const
{
    for (const auto [id, shape] : m_shapes)
    {
        shape->PrintShapeInfo();
    }
}

void Picture::ChangeColor(const std::string& shapeId, const Color color) const
{
    m_shapes.at(shapeId)->SetColor(color);
}

const Color& Picture::GetShapeColor(const std::string& shapeId) const
{
    return m_shapes.at(shapeId)->GetColor();
}

void Picture::AssertShapeExist(const std::string& shapeId) const
{
    if (!m_shapes.contains(shapeId))
    {
        throw std::invalid_argument("Shape not exists");
    }
}

void Picture::AssertShapeNotExist(const std::string& shapeId) const
{
    if (m_shapes.contains(shapeId))
    {
        throw std::invalid_argument("Shape already exists");
    }
}