#pragma once
#include "../IDrawingStrategy.h"

class DrawingTextStrategy final : public IDrawingStrategy
{
public:
    DrawingTextStrategy(std::string  text, float fontSize, const CPoint& position);
    void Draw(std::shared_ptr<ICanvas> canvas, Color color) const override;
    void MoveShape(const CPoint& deltaPoint) override;
    [[nodiscard]] std::string GetParametersInfoAsString() const override;
private:
    std::string m_text;
    float m_fontSize;
    CPoint m_position;
};