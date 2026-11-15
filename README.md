# Object-oriented design coursework

A collection of C++20 exercises exploring object-oriented design and common software design techniques. Each lab is built as a separate CMake target; selected labs also define Catch2 tests.

## Topics and examples

- `lab1/`: duck and shape exercises.
- `lab2/`: a weather-station example, with observer-related interfaces and tests.
- `lab3/`: coffee and stream exercises.
- `lab4/`–`lab6/`: additional design exercises, including a text redactor.
- `lab7/`: a slide/shape model with drawing abstractions and tests.
- `lab8/`–`lab10/`: further coursework projects.

The root `CMakeLists.txt` lists the subprojects and uses Boost Filesystem and Catch2; the slide project additionally uses SFML.

## Build

Requirements: CMake 3.30+, a C++20 compiler, Boost Filesystem, and SFML for the slide application. Catch2 is fetched by CMake.

```bash
cmake -S . -B build
cmake --build build
```

Some dependency locations may need to be configured for your machine. To build or test one exercise, use its target from the root build; test targets are registered with CTest where configured.

## Repository structure

Each `labN/` directory contains one or more standalone exercises. Refer to its `CMakeLists.txt` for target names and dependencies.
