find_package(Magnum REQUIRED
    Shaders
    Text
    Sdl2Application
    GlfwApplication
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS} -Wno-variadic-macros -Wno-multichar -Wno-old-style-cast -Wno-unused-parameter")
#include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_APPLICATION_INCLUDE_DIRS}) # ${SDL2_INCLUDE_DIR})

add_executable(scroll_test_sdl
    main_sdl.cpp
)

target_link_libraries(scroll_test_sdl
    Magnum::Sdl2Application
    Magnum::Magnum
    Magnum::Shaders
    Magnum::Text
)

add_executable(scroll_test_glfw
    main_glfw.cpp
)

target_link_libraries(scroll_test_glfw
    Magnum::GlfwApplication
    Magnum::Magnum
    Magnum::Shaders
    Magnum::Text
)
