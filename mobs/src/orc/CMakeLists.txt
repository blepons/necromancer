add_library(
    orc
    SHARED
    orc.cpp
)

target_link_libraries(
    orc
    PRIVATE mob
    PRIVATE mob_plugin
    PRIVATE plugin_keeper
)

set_target_properties(
    orc
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
