add_library(
    stairs
    stairs.hpp
)

target_include_directories(
    stairs
    INTERFACE .
)

add_subdirectory(downward_stairs)

add_subdirectory(upward_stairs)

target_link_libraries(
    stairs
    PUBLIC downward_stairs
    PUBLIC upward_stairs
)
