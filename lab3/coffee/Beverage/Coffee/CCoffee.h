#pragma once

#include "../Beverages.h"

enum CoffeePortion
{
    DEFAULT,
    DOUBLE
};

class CCoffee : public CBeverage
{
public:
    // "double" + name
    explicit CCoffee(const std::string& description = "Coffee", const CoffeePortion portion)
        : CBeverage(description), m_portion(portion)
    {
    }

    [[nodiscard]] double GetCost() const override
    {
        return 60;
    };

    [[nodiscard]] CoffeePortion GetPortion() const
    {
        return m_portion;
    }
private:
    CoffeePortion m_portion;
};