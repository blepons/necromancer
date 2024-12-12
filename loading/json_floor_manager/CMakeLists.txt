add_library(
    json_floor_manager
    json_floor_manager.hpp json_floor_manager.cpp
)

target_include_directories(
    json_floor_manager
    INTERFACE .
)

target_link_libraries(
    json_floor_manager
    PUBLIC floor_manager
    PUBLIC stage
    PRIVATE entity_builder
    PRIVATE tile_builder
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE hero
)
