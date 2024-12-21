add_library(
    close_door_action
    close_door_action.hpp
)

target_include_directories(
    close_door_action
    INTERFACE .
)

target_link_libraries(
    close_door_action
    PUBLIC entity_action
    PRIVATE stage
    PRIVATE tile
)
