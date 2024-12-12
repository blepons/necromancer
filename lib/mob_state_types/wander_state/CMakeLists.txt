add_library(
    wander_state
    wander_state.hpp wander_state.cpp
)

target_include_directories(
    wander_state
    INTERFACE .
)

target_link_libraries(
    wander_state
    PUBLIC mob_state
    # TODO: remove temporary solution
    PRIVATE rest_action
)
