add_library(
    open_door_action
    open_door_action.hpp
)

target_include_directories(
    open_door_action
    INTERFACE .
)

target_link_libraries(
    open_door_action
    PUBLIC entity_action
    PRIVATE stage
    PRIVATE tile
)
