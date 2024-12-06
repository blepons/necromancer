add_library(
    tile_registry
    tile_registry.hpp tile_registry.cpp
)

target_include_directories(
    tile_registry
    INTERFACE .
)

target_link_libraries(
    tile_registry
    PUBLIC tile
)
