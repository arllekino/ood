#pragma once
#include "../Beverages.h"

enum class CMilkshakeSizeType
{
    BIG,
    MEDIUM,
    SMALL
};

class CMilkshake : public CBeverage
{
    explicit CMilkshake(const CMilkshakeSizeType size)
        : CBeverage("Milkshake " + GetMilkshakeSizeTypeName(size) + "portion"),
        m_size(size)
    {
    }

    [[nodiscard]] double GetCost() const override
    {
        return 40 + GetMilkshakeSizeTypeCost(m_size);
    }
private:
    CMilkshakeSizeType m_size;

    static std::string GetMilkshakeSizeTypeName(const CMilkshakeSizeType size)
    {
        switch (size)
        {
            case CMilkshakeSizeType::BIG:
                return "Big";
            case CMilkshakeSizeType::MEDIUM:
                return "Medium";
            case CMilkshakeSizeType::SMALL:
                return "Small";
            default:
                return "Unknown";
        }
    }

    static double GetMilkshakeSizeTypeCost(const CMilkshakeSizeType size)
    {
        switch (size)
            {
            case CMilkshakeSizeType::BIG:
                return 40;
            case CMilkshakeSizeType::MEDIUM:
                return 20;
            case CMilkshakeSizeType::SMALL:
                return 10;
            default:
                return 0;
        }
    }
};