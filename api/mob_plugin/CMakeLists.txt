add_library(
    mob_plugin
    INTERFACE mob_plugin.hpp
)

target_include_directories(
    mob_plugin
    INTERFACE .
)

target_link_libraries(
    mob_plugin
    INTERFACE nlohmann_json::nlohmann_json
)
