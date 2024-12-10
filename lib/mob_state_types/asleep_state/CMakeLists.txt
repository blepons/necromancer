add_library(
    asleep_state
    asleep_state.hpp asleep_state.cpp
)

target_include_directories(
    asleep_state
    INTERFACE .
)

target_link_libraries(
    asleep_state
    PUBLIC mob_state
    PRIVATE rest_action
)
