//
// Created by Miroslav Aktuganov on 07.09.2025.
//

#include "DuckFunctions.h"
#include "Duck/DecoyDuck.h"
#include "Duck/MallardDuck.h"
#include "Duck/ModelDuck.h"
#include "Duck/RedheadDuck.h"
#include "Duck/RubberDuck.h"

int main()
{
    auto mallardDuck = MallardDuck();
    PlayWithDuck(mallardDuck);

    auto redheadDuck = RedheadDuck();
    PlayWithDuck(redheadDuck);

    auto rubberDuck = RubberDuck();
    PlayWithDuck(rubberDuck);

    auto decoyDuck = DecoyDuck();
    PlayWithDuck(decoyDuck);

    auto modelDuck = ModelDuck();
    PlayWithDuck(modelDuck);

    modelDuck.SetFlyBehavior(std::make_unique<FlyWithWings>());
    PlayWithDuck(modelDuck);

    return 0;
}
