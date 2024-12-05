add_library(
    open_door
    open_door.hpp open_door.cpp
)

target_include_directories(
    open_door
    INTERFACE .
)

target_link_libraries(
    open_door
    PUBLIC tile
    PRIVATE close_door_action
)
