add_library(
    plugin_manager
    plugin_manager.hpp plugin_manager.cpp
)

target_include_directories(
    plugin_manager
    INTERFACE .
)

target_link_libraries(
    plugin_manager
    PUBLIC dynamic_library
    PUBLIC mob_plugin
)
