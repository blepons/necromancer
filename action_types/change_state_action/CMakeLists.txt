add_library(
    change_state_action
    change_state_action.hpp change_state_action.cpp
)

target_include_directories(
    change_state_action
    INTERFACE .
)

target_link_libraries(
    change_state_action
    PUBLIC entity_action
    PUBLIC mob_state
    PRIVATE mob
)
