#pragma once

#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
    explicit CBeverage(const std::string& description) : m_description(description)
    {
    }

    std::string GetDescription() const override
    {
        return m_description;
    }
private:
    std::string m_description;
};