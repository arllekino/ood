cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.0_1/lib/cmake/SFML")
include(FetchContent)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
include_directories(${SFML_INCLUDE_DIRS})

FetchContent_Declare(
        FakeIt
        GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
        GIT_TAG 2.4.1
)
FetchContent_MakeAvailable(FakeIt)
include_directories(${fakeit_SOURCE_DIR}/single_header/standalone)

add_executable(ShapesFabric
        Shape/ShapeType.h
        CPoint/CPoint.h
        Color/Color.cpp
        Color/Color.h
        ICanvas/ICanvas.h
        CCanvas/CCanvas.h
        CCanvas/CCanvas.cpp
        Shape/DrawingStrategy/IDrawingStrategy.h
        Shape/DrawingStrategy/DrawingCircleStrategy/DrawingCircleStrategy.cpp
        Shape/DrawingStrategy/DrawingCircleStrategy/DrawingCircleStrategy.h
        Shape/DrawingStrategy/DrawingRectangleStrategy/DrawingRectangleStrategy.cpp
        Shape/DrawingStrategy/DrawingRectangleStrategy/DrawingRectangleStrategy.h
        Shape/DrawingStrategy/DrawingTriangleStrategy/DrawingTriangleStrategy.cpp
        Shape/DrawingStrategy/DrawingTriangleStrategy/DrawingTriangleStrategy.h
        Shape/DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.cpp
        Shape/DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.h
        Shape/DrawingStrategy/DrawingTextStrategy/DrawingTextStrategy.cpp
        Shape/DrawingStrategy/DrawingTextStrategy/DrawingTextStrategy.h
        Shape/ShapeFactory/ShapeFactory.cpp
        Shape/ShapeFactory/ShapeFactory.h
        ShapesController/ShapesController.cpp
        ShapesController/ShapesController.h
        Shape/Shape.cpp
        Shape/Shape.h
        Picture/Picture.cpp
        Picture/Picture.h
        Shape/DrawingStrategy/DrawingPolygonStrategy/DrawingPolygonStrategy.cpp
        Shape/DrawingStrategy/DrawingPolygonStrategy/DrawingPolygonStrategy.h
        main.cpp
)

add_executable(ShapesFabricTest
        Shape/ShapeType.h
        CPoint/CPoint.h
        Color/Color.cpp
        Color/Color.h
        ICanvas/ICanvas.h
        CCanvas/CCanvas.h
        CCanvas/CCanvas.cpp
        Shape/DrawingStrategy/IDrawingStrategy.h
        Shape/DrawingStrategy/DrawingCircleStrategy/DrawingCircleStrategy.cpp
        Shape/DrawingStrategy/DrawingCircleStrategy/DrawingCircleStrategy.h
        Shape/DrawingStrategy/DrawingRectangleStrategy/DrawingRectangleStrategy.cpp
        Shape/DrawingStrategy/DrawingRectangleStrategy/DrawingRectangleStrategy.h
        Shape/DrawingStrategy/DrawingTriangleStrategy/DrawingTriangleStrategy.cpp
        Shape/DrawingStrategy/DrawingTriangleStrategy/DrawingTriangleStrategy.h
        Shape/DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.cpp
        Shape/DrawingStrategy/DrawingLineStrategy/DrawingLineStrategy.h
        Shape/DrawingStrategy/DrawingTextStrategy/DrawingTextStrategy.cpp
        Shape/DrawingStrategy/DrawingTextStrategy/DrawingTextStrategy.h
        Shape/ShapeFactory/ShapeFactory.cpp
        Shape/ShapeFactory/ShapeFactory.h
        ShapesController/ShapesController.cpp
        ShapesController/ShapesController.h
        Shape/Shape.cpp
        Shape/Shape.h
        Picture/Picture.cpp
        Picture/Picture.h
        Shape/DrawingStrategy/DrawingPolygonStrategy/DrawingPolygonStrategy.cpp
        Shape/DrawingStrategy/DrawingPolygonStrategy/DrawingPolygonStrategy.h
        test/ColorTest.cpp
        test/CPointTest.cpp
        test/DrawingStrategiesTest.cpp
        test/ShapeFactoryTest.cpp
        test/ShapeTest.cpp
)

target_link_libraries(ShapesFabric PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
)

target_link_libraries(ShapesFabricTest PRIVATE Catch2::Catch2WithMain)
target_link_libraries(ShapesFabricTest PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
)
include(CTest)
include(Catch)
catch_discover_tests(ShapesFabricTest)