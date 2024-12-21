add_library(
    summon_move
    summon_move.hpp summon_move.cpp
)

target_include_directories(
    summon_move
    INTERFACE .
)

target_link_libraries(
    summon_move
    PUBLIC move
    PRIVATE spawn_action
    PRIVATE mob
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE do_nothing_action
)
