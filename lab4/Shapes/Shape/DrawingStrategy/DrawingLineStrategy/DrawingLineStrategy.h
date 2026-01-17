#pragma once
#include "../IDrawingStrategy.h"

class DrawingLineStrategy final : public IDrawingStrategy
{
public:
    DrawingLineStrategy(const CPoint& startPoint, const CPoint& endPoint);
    void Draw(std::shared_ptr<ICanvas> canvas, Color color) const override;
    void MoveShape(const CPoint& deltaPoint) override;
    [[nodiscard]] std::string GetParametersInfoAsString() const override;
private:
    CPoint m_startPoint;
    CPoint m_endPoint;
};