set(BOOST_ROOT "/opt/homebrew/opt/boost")
find_package(Boost REQUIRED)

add_executable(adapter
        graphics_lib/graphics_lib.h
        shape_drawing_lib/shape_drawing_lib.h
        modern_graphics_lib/modern_graphics_lib.h
        Adapter/ModernGraphicsLibAdapter.h
        main.cpp
        Adapter/ModernGraphicsClassAdapter.h
)

add_executable(adapterTest
        graphics_lib/graphics_lib.h
        shape_drawing_lib/shape_drawing_lib.h
        modern_graphics_lib/modern_graphics_lib.h
        Adapter/ModernGraphicsLibAdapter.h
        test/test.cpp
        Adapter/ModernGraphicsClassAdapter.h
)


target_include_directories(adapter PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(adapter PRIVATE Boost::headers)
target_include_directories(adapterTest PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(adapterTest PRIVATE Boost::headers)

target_link_libraries(adapterTest PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(adapterTest)