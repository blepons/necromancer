add_library(
    game
    game.hpp game.cpp
)

target_include_directories(
    game
    INTERFACE .
)

target_link_libraries(
    game
    PUBLIC action
    PUBLIC event
    PUBLIC turn_result
    PUBLIC stage
    PUBLIC tile_registry
    PUBLIC undead_registry
    PRIVATE plugin_manager
)
