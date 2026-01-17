//
// Created by Miroslav Aktuganov on 11.09.2025.
//

#include "../Duck/DecoyDuck.h"
#include "../Duck/MallardDuck.h"
#include "../Duck/ModelDuck.h"
#include "../Duck/RedheadDuck.h"
#include "../Duck/RubberDuck.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Duck dance test")
{
    SECTION("Decoy duck")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        const std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        const auto decoyDuck = DecoyDuck();
        decoyDuck.Dance();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.empty());
    }

    SECTION("Mallard duck")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        const std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        const auto mallardDuck = MallardDuck();
        mallardDuck.Dance();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "I'm dancing waltz!\n");
    }

    SECTION("Model duck")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        const auto modelDuck = ModelDuck();
        modelDuck.Dance();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.empty());
    }

    SECTION("Redhead duck")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        const auto redheadDuck = RedheadDuck();
        redheadDuck.Dance();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output == "I'm dancing menuet\n");
    }

    SECTION("Rubber duck")
    {
        std::streambuf* oldCout = std::cout.rdbuf();
        const std::ostringstream buffer;
        std::cout.rdbuf(buffer.rdbuf());

        const auto rubberDuck = RubberDuck();
        rubberDuck.Dance();

        std::string output = buffer.str();
        std::cout.rdbuf(oldCout);

        REQUIRE(output.empty());
    }
}

class MockQuackBehavior final : public IQuackBehavior
{
public:
    void Quack() override
    {
        m_quackCount++;
        std::cout << "Quack!!" << std::endl;
    }

    [[nodiscard]] int GetQuackCount() const
    {
        return m_quackCount;
    }
private:
    int m_quackCount = 0;
};

TEST_CASE("Quack with flying test")
{
    SECTION("Fly with wings")
    {
        const auto quackBehavior = std::make_unique<MockQuackBehavior>();
        auto flyDecorator = FlyWithWingsAndQuack(quackBehavior.get());

        flyDecorator.Fly();
        REQUIRE(quackBehavior->GetQuackCount() == 0);
        flyDecorator.Fly();
        REQUIRE(quackBehavior->GetQuackCount() == 1);
        flyDecorator.Fly();
        flyDecorator.Fly();
        REQUIRE(quackBehavior->GetQuackCount() == 2);
    }
}