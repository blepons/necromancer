add_library(
    wall
    wall.hpp wall.cpp
)

target_include_directories(
    wall
    INTERFACE .
)

target_link_libraries(
    wall
    PUBLIC tile
)
