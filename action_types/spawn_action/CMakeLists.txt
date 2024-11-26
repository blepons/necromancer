add_library(
    spawn_action
    spawn_action.hpp spawn_action.cpp
)

target_include_directories(
    spawn_action
    INTERFACE .
)

target_link_libraries(
    spawn_action
    PUBLIC entity_action
    PRIVATE mob
    PRIVATE mob_plugin
)
