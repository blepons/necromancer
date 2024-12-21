add_library(
    necromancy_action
    necromancy_action.hpp necromancy_action.cpp
)

target_include_directories(
    necromancy_action
    INTERFACE .
)

target_link_libraries(
    necromancy_action
    PUBLIC entity_action
    PRIVATE corpse
    PRIVATE hero
    PRIVATE wander_state
)
