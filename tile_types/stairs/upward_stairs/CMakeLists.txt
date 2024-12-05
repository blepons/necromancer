add_library(
    upward_stairs
    upward_stairs.hpp upward_stairs.cpp
)

target_include_directories(
    upward_stairs
    INTERFACE .
)

target_link_libraries(
    upward_stairs
    PUBLIC tile
)
