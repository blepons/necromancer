add_library(
    next_floor_action
    next_floor_action.hpp next_floor_action.cpp
)

target_include_directories(
    next_floor_action
    INTERFACE .
)

target_link_libraries(
    next_floor_action
    PUBLIC action
)
