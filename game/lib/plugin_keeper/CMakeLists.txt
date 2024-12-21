add_library(
    plugin_keeper
    plugin_keeper.hpp plugin_keeper.cpp
)

target_include_directories(
    plugin_keeper
    INTERFACE .
)

target_link_libraries(
    plugin_keeper
    PRIVATE plugin_manager
)
