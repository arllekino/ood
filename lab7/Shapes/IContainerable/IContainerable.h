#pragma once
#include <memory>
#include "../IShape.h"

class IContainerable
{
public:
    virtual ~IContainerable() = default;

    virtual void AddShape(const std::shared_ptr<IShape>& shape) = 0;
};
