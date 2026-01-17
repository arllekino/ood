#pragma once

#include <cassert>
#include <memory>
#include <iostream>

#include "Dance/IDanceBehavior.h"
#include "Fly/FlyWithWingsAndQuack.h"
#include "Fly/IFlyBehavior.h"
#include "Quack/IQuackBehavior.h"

class Duck
{
public:
    Duck(
        std::unique_ptr<IFlyBehavior>&& flyBehavior,
        std::unique_ptr<IQuackBehavior>&& quackBehavior,
        std::unique_ptr<IDanceBehavior>&& danceBehavior)
            : m_quackBehavior(std::move(quackBehavior)),
            m_danceBehavior(std::move(danceBehavior))
    {
        assert(m_quackBehavior);
        SetFlyBehavior(std::move(flyBehavior));
    }

    void Quack() const
    {
        m_quackBehavior->Quack();
    }

    static void Swim()
    {
        std::cout << "I'm swimming" << std::endl;
    }

    void Fly() const
    {
        m_flyBehavior->Fly();
    }

    virtual void Dance() const
    {
        m_danceBehavior->Dance();
    }

    void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
    {
        assert(flyBehavior);
        m_flyBehavior = std::make_unique<FlyWithWingsAndQuack>(m_quackBehavior.get());
    }

    virtual void Display() const = 0;
    virtual ~Duck() = default;
private:
    std::unique_ptr<IFlyBehavior> m_flyBehavior;
    std::unique_ptr<IQuackBehavior> m_quackBehavior;
    std::unique_ptr<IDanceBehavior> m_danceBehavior;
};