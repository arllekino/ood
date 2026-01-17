cmake_minimum_required(VERSION 3.30)
project(ood)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS filesystem)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.0
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(lab1/DuckDuck)
add_subdirectory(lab1/FunctionalDuck)
add_subdirectory(lab1/Shapes)

add_subdirectory(lab2)

add_subdirectory(lab3/coffee)
add_subdirectory(lab3/stream)

add_subdirectory(lab4/Shapes)

add_subdirectory(lab5/redactor)

add_subdirectory(lab6/task1)

add_subdirectory(lab7)

add_subdirectory(lab8)

add_subdirectory(lab9)