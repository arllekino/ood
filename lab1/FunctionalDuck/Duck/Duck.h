#pragma once

#include <iostream>

#include "Dance/DanceBehavior.h"
#include "Fly/FlyBehavior.h"

class Duck
{
public:
    Duck(
        FlyBehavior flyBehavior,
        QuackBehavior quackBehavior,
        DanceBehavior danceBehavior)
            : m_flyBehavior(std::move(flyBehavior)),
            m_quackBehavior(std::move(quackBehavior)),
            m_danceBehavior(std::move(danceBehavior))
    {
    }

    void Quack() const
    {
        m_quackBehavior();
    }

    static void Swim()
    {
        std::cout << "I'm swimming" << std::endl;
    }

    void Fly() const
    {
        m_flyBehavior();
    }

    virtual void Dance() const
    {
        m_danceBehavior();
    }

    void SetFlyBehavior(FlyBehavior flyBehavior)
    {
        m_flyBehavior = std::move(flyBehavior);
    }

    virtual void Display() const = 0;
    virtual ~Duck() = default;
private:
    FlyBehavior m_flyBehavior;
    QuackBehavior m_quackBehavior;
    DanceBehavior m_danceBehavior;
};
