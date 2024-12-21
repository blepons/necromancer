add_library(
    walk_action
    walk_action.hpp walk_action.cpp
)

target_include_directories(
    walk_action
    INTERFACE .
)

target_link_libraries(
    walk_action
    PUBLIC direction
    PUBLIC entity_action
    PRIVATE stage
    PRIVATE hero
    PRIVATE rest_action
    PRIVATE attack_action
    PRIVATE tile
)
