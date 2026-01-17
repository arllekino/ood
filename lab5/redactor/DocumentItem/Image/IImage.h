#pragma once
#include "../../Path/Path.h"


class IImage
{
public:
    virtual Path GetPath() const = 0;
    virtual unsigned GetWidth() const = 0;
    virtual unsigned GetHeight() const = 0;
    virtual void Resize(unsigned width, unsigned height) = 0;
    virtual ~IImage() = default;
};

using IImagePtr = std::shared_ptr<IImage>;