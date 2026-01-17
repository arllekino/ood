#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Shape/Shape.h"
#include "../ICanvas/ICanvas.h"
#include "../CCanvas/CCanvas.h"

class Picture
{
public:
    explicit Picture(sf::RenderWindow& window);

    void AddShape(std::shared_ptr<shapes::Shape> shape);
    void DrawShape(const std::string& shapeId);
    void DrawShapes();
    void DrawPicture() const;
    void MoveShape(const std::string& shapeId, const CPoint& deltaPoint) const;
    void MovePicture(const CPoint& deltaPoint);
    void DeleteShape(const std::string& shapeId);
    void List() const;
    void ChangeColor(const std::string& shapeId, Color color) const;
    const Color& GetShapeColor(const std::string& shapeId) const;

    void AssertShapeExist(const std::string& shapeId) const;
    void AssertShapeNotExist(const std::string& shapeId) const;
private:
    std::shared_ptr<ICanvas> m_canvas;
    std::unordered_map<std::string, std::shared_ptr<shapes::Shape>> m_shapes;
    std::unordered_map<std::string, std::shared_ptr<shapes::Shape>> m_shapesToDraw;
};
