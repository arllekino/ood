#pragma once

#include "CCoffee.h"

class CLatte : public CCoffee
{
public:
    explicit CLatte(const CoffeePortion portion)
        : CCoffee(GetNameByPortion(portion), portion)
    {}

    [[nodiscard]] double GetCost() const override
    {
        return GetCostByPortion();
    }

private:
    static std::string GetNameByPortion(const CoffeePortion portion)
    {
        switch (portion)
        {
            case DEFAULT:
                return "Latte";
            case DOUBLE:
                return "Double Latte";
            default:
                return "Unknown";
        }
    }

    [[nodiscard]] double GetCostByPortion() const
    {
        switch (GetPortion()) {
            case DEFAULT:
                return 90;
            case DOUBLE:
                return 130;
            default:
                return 0;
        }
    }
};
