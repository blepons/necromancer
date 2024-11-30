add_library(
    plugin_manager
    SHARED
    plugin_manager.hpp plugin_manager.cpp
)

target_include_directories(
    plugin_manager
    INTERFACE .
)

target_link_libraries(
    plugin_manager
    PUBLIC mob_plugin
)
