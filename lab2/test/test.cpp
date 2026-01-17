//
// Created by Miroslav Aktuganov on 27.09.2025.
//

#include <iostream>

#include "TestObservable.h"
#include "TestObservableForTask4.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("WeatherStation")
{
    SECTION("WeatherStation OnNotifyDelete")
    {
        TestObservable observable;
        TestObserver observer1;
        TestObserver observer2;

        observable.RegisterObserver(observer1, 0);
        observable.RegisterObserver(observer2, 0);

        bool removed = false;
        bool observer1Notified = false;

        observer1.SetOnUpdate([&observer1Notified]() {
            observer1Notified = true;
        });

        observer2.SetOnUpdate([&]() {
            observable.RemoveObserver(observer2);
            removed = true;
        });

        observable.NotifyObservers();

        REQUIRE(removed);
        REQUIRE(observer1Notified);
        REQUIRE(observable.GetObserverCount() == 1);
    }

    SECTION("WeatherStation Priority")
    {
        auto observer1 = TestObserver();
        auto observer2 = TestObserver();
        auto observer3 = TestObserver();
        auto observable = TestObservable();

        std::stringstream buffer;

        observer1.SetOnUpdate([&] {
            buffer << "Hello from observer1" << std::endl;
        });
        observer2.SetOnUpdate([&] {
            buffer << "Hello from observer2" << std::endl;
        });
        observer3.SetOnUpdate([&] {
            buffer << "Hello from observer3" << std::endl;
        });

        observable.RegisterObserver(observer1, 0);
        observable.RegisterObserver(observer3, 1);
        observable.RegisterObserver(observer2, 0);

        observable.NotifyObservers();

        std::string output = buffer.str();

        REQUIRE(output == "Hello from observer3\nHello from observer1\nHello from observer2\n");
    }

    // три обсервера, происходвеит уведомление, удаляю один из обсерверов, происходит уведомление
    // обсервер действительно удалился и что все корректно работает
    SECTION("Three observers with removal between notifications")
    {
        TestObservable observable;
        TestObserver observer1;
        TestObserver observer2;
        TestObserver observer3;

        observable.RegisterObserver(observer1, 0);
        observable.RegisterObserver(observer2, 1);
        observable.RegisterObserver(observer3, 0);

        std::stringstream buffer;

        observer1.SetOnUpdate([&buffer]() {
            buffer << "Hello from observer1" << std::endl;
        });

        observer2.SetOnUpdate([&observable, &observer2, &buffer]() {
            buffer << "Hello from observer2" << std::endl;
            observable.RemoveObserver(observer2);
        });
        observer3.SetOnUpdate([&buffer]() {
            buffer << "Hello from observer3" << std::endl;
        });

        observable.NotifyObservers();

        REQUIRE(buffer.str() == "Hello from observer2\nHello from observer1\nHello from observer3\n");
        REQUIRE(observable.GetObserverCount() == 2);
    }

    SECTION("WeatherStation more then 1 observables")
    {
        auto observer = TestObserverForTask4();
        auto observable1 = TestObservableForTask4();
        auto observable2 = TestObservableForTask4();

        observable1.RegisterObserver(observer, 0);
        observable2.RegisterObserver(observer, 0);

        observer.SetOnUpdate([&observable1](const IObservable<TestStructForTask4>& observable) {
            REQUIRE(&observable1 == &observable);
        });
        observable1.NotifyObservers();

        observer.SetOnUpdate([&observable2](const IObservable<TestStructForTask4>& observable) {
            REQUIRE(&observable2 == &observable);
        });
        observable2.NotifyObservers();
    }
}