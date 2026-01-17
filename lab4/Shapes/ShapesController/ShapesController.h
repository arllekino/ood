#pragma once

#include <vector>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "../Picture/Picture.h"
#include "../Shape/Shape.h"
#include "../Shape/ShapeFactory/ShapeFactory.h"

class ShapesController
{
public:
    explicit ShapesController(sf::RenderWindow& window);

    void OnInput(std::istream& input);
    void DrawPicture() const;
private:
    Picture m_picture;
    ShapeFactory m_shapeFactory;
    void ControlShapesByMessage(std::stringstream& ss);

    void OnAddShape(std::stringstream& ss);

    void OnMoveShape(std::stringstream& ss) const;
    void OnMovePicture(std::stringstream& ss);
    void OnDeleteShape(std::stringstream& ss);
    void OnList() const;
    void OnChangeColor(std::stringstream& ss) const;
    void OnChangeShape(std::stringstream& ss);
    void OnDrawShape(std::stringstream& ss);
    void OnDrawPicture();

    static uint32_t StringToUint32(const std::string& str);
    static shapes::ShapeType StringToShapeType(const std::string& str);
};
