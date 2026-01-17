#pragma once
#include "../IDrawingStrategy.h"

class DrawingCircleStrategy final : public IDrawingStrategy
{
public:
    DrawingCircleStrategy(const CPoint& center, float radius);
    void Draw(std::shared_ptr<ICanvas> canvas, Color color) const override;
    void MoveShape(const CPoint& deltaPoint) override;
    [[nodiscard]] std::string GetParametersInfoAsString() const override;
private:
    CPoint m_center;
    float m_radius;
};
