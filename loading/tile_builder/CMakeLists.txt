add_library(
    tile_builder
    tile_builder.hpp tile_builder.cpp
)

target_include_directories(
    tile_builder
    INTERFACE .
)

target_link_libraries(
    tile_builder
    PUBLIC tile
    PUBLIC game
)
