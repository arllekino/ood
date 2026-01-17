#pragma once
#include "../IDrawingStrategy.h"

class DrawingTriangleStrategy final : public IDrawingStrategy
{
public:
    DrawingTriangleStrategy(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3);
    void Draw(std::shared_ptr<ICanvas> canvas, Color color) const override;
    void MoveShape(const CPoint& deltaPoint) override;
    [[nodiscard]] std::string GetParametersInfoAsString() const override;
private:
    CPoint m_vertex1;
    CPoint m_vertex2;
    CPoint m_vertex3;
};