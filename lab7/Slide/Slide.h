#pragma once
#include <vector>
#include <memory>

#include "../Canvas/IDrawable.h"
#include "../Shapes/IShape.h"
#include "../Shapes/IContainerable/IContainerable.h"

class Slide : public IDrawable, public IContainerable
{
public:
    void AddShape(const std::shared_ptr<IShape>& shape) override
    {
        m_shapes.push_back(shape);
    }

    void Draw(ICanvas& canvas) override
    {
        for (auto& shape : m_shapes)
        {
            shape->Draw(canvas);
        }
    }

private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
};