add_library(
    closed_door
    closed_door.hpp closed_door.cpp
)

target_include_directories(
    closed_door
    INTERFACE .
)

target_link_libraries(
    closed_door
    PUBLIC tile
    PRIVATE open_door_action
)
