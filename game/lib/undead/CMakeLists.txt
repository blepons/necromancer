add_library(
    undead
    # TODO: make it SHARED?
    undead.hpp undead.cpp
)

target_include_directories(
    undead
    INTERFACE .
)

target_link_libraries(
    undead
    PUBLIC mob
    PRIVATE disappear_action
)
