add_library(
    fov
    fov.hpp fov.cpp
)

target_include_directories(
    fov
    INTERFACE .
)

target_link_libraries(
    fov
    PRIVATE point
    PRIVATE stage
    PRIVATE tile
)
