add_library(
    pathfinder
    pathfinder.hpp pathfinder.cpp
)

target_include_directories(
    pathfinder
    INTERFACE .
)

target_link_libraries(
    pathfinder
    PUBLIC point
    PUBLIC direction
    PUBLIC tile
    PRIVATE mob
    PRIVATE stage
    PRIVATE cost_priority_queue
)
