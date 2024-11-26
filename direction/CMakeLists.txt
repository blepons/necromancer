add_library(
    direction
    INTERFACE direction.hpp
)

target_include_directories(
    direction
    INTERFACE .
)

target_link_libraries(
    direction
    INTERFACE point
)
