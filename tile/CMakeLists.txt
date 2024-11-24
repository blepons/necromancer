add_library(
    tile
    tile.hpp tile.cpp
)

target_include_directories(
    tile
    INTERFACE .
)

target_link_libraries(
    tile
    PUBLIC passability
    PUBLIC tile_type
)
