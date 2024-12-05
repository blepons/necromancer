add_library(
    lava
    lava.hpp lava.cpp
)

target_include_directories(
    lava
    INTERFACE .
)

target_link_libraries(
    lava
    PUBLIC tile
    PRIVATE lava_burn_action
)
