add_library(
    stage
    stage.hpp stage.cpp
)

target_include_directories(
    stage
    INTERFACE .
)

target_link_libraries(
    stage
    PUBLIC entity
    PRIVATE game
    PRIVATE fov
    PUBLIC matrix
    PUBLIC tile
    PRIVATE line
)
