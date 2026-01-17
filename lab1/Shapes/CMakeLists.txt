cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.0_1/lib/cmake/SFML")
include(FetchContent)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
include_directories(${SFML_INCLUDE_DIRS})

add_executable(Shapes
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
        main.cpp
)

target_link_libraries(Shapes PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
)