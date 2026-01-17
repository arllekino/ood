#pragma once

#include "../Beverages.h"

class CTea : public CBeverage
{
public:
    explicit CTea(const std::string& name) : CBeverage(name)
    {}

    [[nodiscard]] double GetCost() const override
    {
        return 100;
    }
};
