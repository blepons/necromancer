add_library(
    stone_golem
    SHARED
    stone_golem.cpp
)

target_link_libraries(
    stone_golem
    PRIVATE mob
    PRIVATE mob_plugin
    PRIVATE plugin_keeper
    PRIVATE hero
    PRIVATE disappear_action
    PRIVATE set_block_action
)

set_target_properties(
    stone_golem
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
