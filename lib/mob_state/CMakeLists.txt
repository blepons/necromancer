add_library(
    mob_state
    mob_state.hpp mob_state.cpp
)

target_include_directories(
    mob_state
    INTERFACE .
)

target_link_libraries(
    mob_state
    PUBLIC point
    PUBLIC mob
    # PUBLIC action
)
