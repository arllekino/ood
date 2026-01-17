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
    std::string shapeId, color, shapeTypeStr;
    ss >> shapeId >> color >> shapeTypeStr;
    m_picture.AssertShapeNotExist(shapeId);

    shapes::Shape tempShape = CreateShape(
        shapeId,
        Color(color),
        StringToShapeType(shapeTypeStr),
        ss
    );

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
            CreateShape(
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

shapes::Shape ShapesController::CreateShape(
    const std::string& shapeId,
    const Color color,
    const shapes::ShapeType type,
    std::stringstream& ss) const
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
        default:
            assert(false);
    }
}

shapes::Shape ShapesController::CreateCircle(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss) const
{
    std::string posX, posY, radius;
    ss >> posX >> posY >> radius;
    return m_shapeFactory.CreateCircleImpl(
        shapeId,
        color,
        CPoint(std::stof(posX), std::stof(posY)),
        std::stof(radius)
    );
}

shapes::Shape ShapesController::CreateRectangle(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss) const
{
    std::string posX, posY, width, height;
    ss >> posX >> posY >> width >> height;
    return m_shapeFactory.CreateRectangleImpl(
        shapeId,
        color,
        CPoint(std::stof(posX), std::stof(posY)),
        std::stof(width),
        std::stof(height)
    );
}

shapes::Shape ShapesController::CreateLine(
    const std::string& shapeId,
    const Color color,
    std::stringstream& ss) const
{
    std::string posX1, posY1, posX2, posY2;
    ss >> posX1 >> posY1 >> posX2 >> posY2;
    return m_shapeFactory.CreateLineImpl(
        shapeId,
        color,
        CPoint(std::stof(posX1), std::stof(posY1)),
        CPoint(std::stof(posX2), std::stof(posY2))
    );
}

shapes::Shape ShapesController::CreateText(
    const std::string& shapeId,
    const Color color,
    std::stringstream &ss) const
{
    std::string posX, posY, fontSizeStr, text;
    ss >> posX >> posY >> fontSizeStr >> text;
    return m_shapeFactory.CreateTextShapeImpl(
        shapeId,
        color,
        CPoint(std::stof(posX), std::stof(posY)),
        std::stof(fontSizeStr),
        text
    );
}

shapes::Shape ShapesController::CreateTriangle(
    const std::string& shapeId,
    Color color,
    std::stringstream &ss) const
{
    std::string posX1, posY1, posX2, posY2, posX3, posY3;
    ss >> posX1 >> posY1 >> posX2 >> posY2 >> posX3 >> posY3;
    return m_shapeFactory.CreateTriangleImpl(
        shapeId,
        color,
        CPoint(std::stof(posX1), std::stof(posY1)),
        CPoint(std::stof(posX2), std::stof(posY2)),
        CPoint(std::stof(posX3), std::stof(posY3))
    );
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
    throw std::invalid_argument("Invalid shape type string: " + str);
}