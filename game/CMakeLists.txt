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
    PUBLIC event
    PUBLIC turn_result
    PUBLIC stage
    PRIVATE plugin_manager
)
