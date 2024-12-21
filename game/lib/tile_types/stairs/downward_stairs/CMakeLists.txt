add_library(
    downward_stairs
    downward_stairs.hpp downward_stairs.cpp
)

target_include_directories(
    downward_stairs
    INTERFACE .
)

target_link_libraries(
    downward_stairs
    PUBLIC tile
    PRIVATE game
    PRIVATE stage
    PRIVATE hero
    PRIVATE next_floor_action
)

