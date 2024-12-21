add_library(
    ui_drawer
    ui_drawer.hpp ui_drawer.cpp
)

target_include_directories(
    ui_drawer
    INTERFACE .
)

target_link_libraries(
    ui_drawer
    PUBLIC sfml-graphics
    PUBLIC game
    PRIVATE hero
)
