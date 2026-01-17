#pragma once
#include <memory>

#include "FlyWithWings.h"
#include "IFlyBehavior.h"
#include "../Quack/IQuackBehavior.h"

class FlyWithWingsAndQuack final : public IFlyBehavior
{
public:
    explicit FlyWithWingsAndQuack(IQuackBehavior* quackBehavior)
        : m_quackBehavior(quackBehavior)
    {
    }

    void Fly() override
    {
        std::cout << "I'm flying with wings!!" << std::endl;
        m_flightCount++;
        if (m_flightCount > 0
            && m_flightCount % 2 == 0
            && m_quackBehavior != nullptr)
        {
            m_quackBehavior->Quack();
        }
    }

private:
    IQuackBehavior* m_quackBehavior;
    int m_flightCount = 0;
};
