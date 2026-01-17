#pragma once

template<typename T>
class ICloneable
{
public:
    virtual ~ICloneable() = default;
    virtual T Clone() const = 0;
};