cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

add_executable(WeatherStation main.cpp
        Observer/IObserver.h
        Observer/WeatherData.h
        Observer/WeatherDataCharacteristicStat.h)

add_executable(WeatherStationTest
        test/TestObservable.h
        test/TestObservableForTask4.h
        test/test.cpp
)

target_link_libraries(WeatherStationTest PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(WeatherStationTest)