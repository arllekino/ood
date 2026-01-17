#pragma once
#include "../IDrawingStrategy.h"

class DrawingRectangleStrategy final : public IDrawingStrategy
{
public:
    DrawingRectangleStrategy(const CPoint& startPoint, const CPoint& endPoint);
    void Draw(std::shared_ptr<ICanvas> canvas, Color color) const override;
    void MoveShape(const CPoint& deltaPoint) override;
    [[nodiscard]] std::string GetParametersInfoAsString() const override;
private:
    CPoint m_startPoint;
    CPoint m_endPoint;

    [[nodiscard]] CPoint GetLeftTop() const;
    [[nodiscard]] CPoint GetRightTop() const;
    [[nodiscard]] CPoint GetRightBottom() const;
    [[nodiscard]] CPoint GetLeftBottom() const;
};