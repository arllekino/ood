add_executable(gumballMachine main.cpp
        GumballMachines/IGumballMachine/IGumballMachine.h
        States/IState/IState.h
        States/SoldState.h
        States/SoldOutState.h
        States/HasQuarterState.h
        States/NoQuarterState.h
        GumballMachines/GumballMachine.h
        GumballMachines/MultiGumballMachine.h
        GumballMachines/NaiveMultiGumballMachine.h
        States/MultiMachineStates/HasQuartersState.h
        States/MultiMachineStates/NoQuartersState.h
        States/MultiMachineStates/SoldOutState.h
        States/MultiMachineStates/SoldState.h)

add_executable(gumballMachineTest test/test.cpp
        GumballMachines/IGumballMachine/IGumballMachine.h
        States/IState/IState.h)

add_executable(multiMachineTest test/MultiMachineTests.cpp
        GumballMachines/IGumballMachine/IMultiGumballMachine.h
        GumballMachines/MultiGumballMachine.h
        GumballMachines/NaiveMultiGumballMachine.h
        States/IState/IState.h
        States/MultiMachineStates/HasQuartersState.h
        States/MultiMachineStates/SoldOutState.h
        States/MultiMachineStates/SoldState.h
        States/MultiMachineStates/NoQuartersState.h
        GumballMachines/IGumballMachine/IReplenishable.h
        States/IState/IReplenishableState.h
)

add_executable(MultiMachineTestWithReplenish
        test/MultiMachineTestWithReplenish.cpp
        GumballMachines/IGumballMachine/IMultiGumballMachine.h
        GumballMachines/MultiGumballMachine.h
        GumballMachines/NaiveMultiGumballMachine.h
        States/IState/IState.h
        States/MultiMachineStates/HasQuartersState.h
        States/MultiMachineStates/SoldOutState.h
        States/MultiMachineStates/SoldState.h
        States/MultiMachineStates/NoQuartersState.h
        GumballMachines/IGumballMachine/IReplenishable.h
        States/IState/IReplenishableState.h

)

target_link_libraries(gumballMachineTest PRIVATE Catch2::Catch2WithMain)
target_link_libraries(multiMachineTest PRIVATE Catch2::Catch2WithMain)
target_link_libraries(MultiMachineTestWithReplenish PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(gumballMachineTest)
catch_discover_tests(multiMachineTest)
catch_discover_tests(MultiMachineTestWithReplenish)