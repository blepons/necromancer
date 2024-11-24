add_library(
    tile_type
    tile_type.hpp tile_type.cpp
)

target_include_directories(
    tile_type
    INTERFACE .
)

target_link_libraries(
    tile_type
    PRIVATE passability
    PRIVATE point
)
