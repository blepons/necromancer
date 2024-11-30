add_library(
    polymorph_action
    polymorph_action.hpp polymorph_action.cpp
)

target_include_directories(
    polymorph_action
    INTERFACE .
)

target_link_libraries(
    polymorph_action
    PUBLIC entity_action
    PRIVATE mob
    PRIVATE mob_plugin
    PRIVATE nlohmann_json::nlohmann_json
)
