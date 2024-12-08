add_library(
    floor
    floor.hpp floor.cpp
)

target_include_directories(
    floor
    INTERFACE .
)

target_link_libraries(
    floor
    PUBLIC tile
)
