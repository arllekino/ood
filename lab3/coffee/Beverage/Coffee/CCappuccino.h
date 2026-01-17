#pragma once

#include "CCoffee.h"

class CCappuccino : public CCoffee
{
public:
    explicit CCappuccino(const CoffeePortion portion)
        : CCoffee(GetCappuccinoNameByPortion(portion), portion)
    {
    }

    [[nodiscard]] double GetCost() const override
    {
        return GetCostByPortion();
    }
private:
    static std::string GetCappuccinoNameByPortion(const CoffeePortion portion)
    {
        switch (portion)
        {
            case DEFAULT:
                return "Cappuccino";
            case DOUBLE:
                return "Double Cappuccino";
            default:
                return "Cappuccino";
        }
    }

    [[nodiscard]] double GetCostByPortion() const
    {
        switch (GetPortion())
        {
            case DEFAULT:
                return 80;
            case DOUBLE:
                return 120;
            default:
                return 0;
        }
    }
};