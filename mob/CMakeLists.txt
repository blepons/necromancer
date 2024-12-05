add_library(
    mob
    # TODO: make it shared?
    mob.hpp mob.cpp
)

target_include_directories(
    mob
    INTERFACE .
)

target_link_libraries(
    mob
    PUBLIC entity
    PUBLIC attack
    PUBLIC move
    PUBLIC mob_state
    PRIVATE asleep_state
    PRIVATE wander_state
    PRIVATE change_state_action
    PRIVATE stage
)
