#pragma once
#include <limits>

class WeatherDataCharacteristicStat
{
public:
    explicit WeatherDataCharacteristicStat(std::string name)
        : m_name(std::move(name))
    {
    }

    void UpdateStat(const double value)
    {
        if (m_min > value)
        {
            m_min = value;
        }
        if (m_max < value)
        {
            m_max = value;
        }
        m_accumulator += value;
        ++m_countAccumulator;
    }

    void PrintStat() const
    {
        std::cout << "Max " << m_name << " " << m_max << std::endl;
        std::cout << "Min " << m_name << " " << m_min << std::endl;
        std::cout << "Average " << m_name << " " << (m_accumulator / m_countAccumulator) << std::endl;
        std::cout << "----------------" << std::endl;
    }
private:
    std::string m_name;
    double m_min = std::numeric_limits<double>::infinity();
    double m_max = -std::numeric_limits<double>::infinity();
    double m_accumulator = 0;
    unsigned m_countAccumulator = 0;
};
