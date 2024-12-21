add_library(
    renderer
    renderer.hpp renderer.cpp
)

target_include_directories(
    renderer
    INTERFACE .
)

target_link_libraries(
    renderer
    PUBLIC game
    PUBLIC sfml-graphics
    PUBLIC ui_drawer
    PUBLIC direction
    PRIVATE hero
)
