#include "ShapesController.h"

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

ShapesController::ShapesController(sf::RenderWindow& window)
    : m_picture(window)
{
}

void ShapesController::OnInput(std::istream& input)
{
    std::string message;
    std::getline(input, message);

    try
    {
        std::stringstream ss(message);
        ControlShapesByMessage(ss);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ShapesController::DrawPicture() const
{
    m_picture.DrawPicture();
}

void ShapesController::ControlShapesByMessage(std::stringstream& ss)
{
    static const std::unordered_map<std::string, std::function<void()>> commands = {
        { "AddShape", [this, &ss]() { OnAddShape(ss); } },
        { "MoveShape", [this, &ss]() { OnMoveShape(ss); } },
        { "MovePicture", [this, &ss]() { OnMovePicture(ss); } },
        { "DeleteShape", [this, &ss]() { OnDeleteShape(ss); } },
        { "List", [this]() { OnList(); } },
        { "ChangeColor", [this, &ss]() { OnChangeColor(ss); } },
        { "ChangeShape", [this, &ss]() { OnChangeShape(ss); } },
        { "DrawShape", [this, &ss]() { OnDrawShape(ss); } },
        { "DrawPicture", [this]() { OnDrawPicture(); } }
    };;
    std::string message;
    ss >> message;
    if (const auto it = commands.find(message); it != commands.end())
    {
        it->second();
    }
    else
    {
        throw std::invalid_argument("Invalid command");
    }
}

void ShapesController::OnAddShape(std::stringstream& ss)
{
    std::string shapeId, colorStr, shapeTypeStr;
    ss >> shapeId >> colorStr >> shapeTypeStr;
    m_picture.AssertShapeNotExist(shapeId);

    shapes::Shape tempShape = m_shapeFactory.CreateShape(
        shapeId,
        Color(colorStr),
        StringToShapeType(shapeTypeStr),
        ss);

    m_picture.AddShape(std::make_shared<shapes::Shape>(std::move(tempShape)));
}

void ShapesController::OnMoveShape(std::stringstream& ss) const {
    std::string shapeId, dx, dy;
    ss >> shapeId >> dx >> dy;
    m_picture.MoveShape(
        shapeId,
        CPoint(std::stof(dx), std::stof(dy))
    );
}

void ShapesController::OnMovePicture(std::stringstream& ss)
{
    std::string dx, dy;
    ss >> dx >> dy;
    m_picture.MovePicture(
        CPoint(std::stof(dx), std::stof(dy))
    );
}

void ShapesController::OnDeleteShape(std::stringstream& ss)
{
    std::string shapeId;
    ss >> shapeId;
    m_picture.DeleteShape(shapeId);
}

void ShapesController::OnList() const
{
    m_picture.List();
}

void ShapesController::OnChangeColor(std::stringstream& ss) const
{
    std::string shapeId, color;
    ss >> shapeId >> color;
    m_picture.ChangeColor(shapeId, Color(color));
}

void ShapesController::OnChangeShape(std::stringstream& ss)
{
    std::string shapeId, shapeTypeStr;
    ss >> shapeId >> shapeTypeStr;

    m_picture.AssertShapeExist(shapeId);
    const auto shapeColor = m_picture.GetShapeColor(shapeId);
    m_picture.AddShape(
        std::make_shared<shapes::Shape>(
            m_shapeFactory.CreateShape(
                shapeId,
                shapeColor,
                StringToShapeType(shapeTypeStr),
                ss
            )
        )
    );
}

void ShapesController::OnDrawShape(std::stringstream& ss)
{
    std::string shapeId;
    ss >> shapeId;
    m_picture.DrawShape(shapeId);
}

void ShapesController::OnDrawPicture()
{
    m_picture.DrawShapes();
}

uint32_t ShapesController::StringToUint32(const std::string& str)
{
    if (str.length() != 7)
    {
        throw std::invalid_argument("Invalid color format. Expected HEX string like this '#FFFFFF' .");
    }

    const uint32_t color = std::stoul(str, nullptr, 16);

    const uint8_t r = (color >> 16) & 0xFF;
    const uint8_t g = (color >> 8) & 0xFF;
    const uint8_t b = color & 0xFF;

    return sf::Color(r, g, b).toInteger();
}

shapes::ShapeType ShapesController::StringToShapeType(const std::string& str)
{
    if (str == "circle")
    {
        return shapes::ShapeType::CIRCLE;
    }
    if (str == "rectangle")
    {
        return shapes::ShapeType::RECTANGLE;
    }
    if (str == "triangle")
    {
        return shapes::ShapeType::TRIANGLE;
    }
    if (str == "line")
    {
        return shapes::ShapeType::LINE;
    }
    if (str == "text")
    {
        return shapes::ShapeType::TEXT;
    }
    if (str == "polygon")
    {
        return shapes::ShapeType::POLYGON;
    }
    throw std::invalid_argument("Invalid shape type string: " + str);
}