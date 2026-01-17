set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.0_1/lib/cmake/SFML")
include(FetchContent)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
include_directories(${SFML_INCLUDE_DIRS})


add_executable(slides
        Shapes/IShape.h
        Canvas/ICanvas.h
        Canvas/IDrawable.h
        Slide/Slide.h
        Point/Point.h
        Color/Color.h
        Shapes/Rectangle.h
        Shapes/Triangle.h
        Shapes/Ellipse.h
        Shapes/ShapeGroup.h
        Shapes/ShapeProperties/FillStyle.h
        Shapes/ShapeProperties/LineStyle.h
        Shapes/ICloneable/ICloneable.h
        Canvas/CCanvas.h
        Shapes/IContainerable/IContainerable.h
        main.cpp
)

add_executable(testSlide
        Shapes/IShape.h
        Canvas/ICanvas.h
        Canvas/IDrawable.h
        Slide/Slide.h
        Point/Point.h
        Color/Color.h
        Shapes/Rectangle.h
        Shapes/Triangle.h
        Shapes/Ellipse.h
        Shapes/ShapeGroup.h
        Shapes/ShapeProperties/FillStyle.h
        Shapes/ShapeProperties/LineStyle.h
        Shapes/ICloneable/ICloneable.h
        Canvas/CCanvas.h
        Shapes/IContainerable/IContainerable.h
        test/test.cpp
)

target_link_libraries(slides PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
)
target_link_libraries(testSlide PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(testSlide)