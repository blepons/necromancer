add_library(
    ethereal_golem
    SHARED
    ethereal_golem.cpp
)

target_link_libraries(
    ethereal_golem
    PRIVATE mob
    PRIVATE mob_plugin
    PRIVATE plugin_keeper
    PRIVATE hero
    PRIVATE disappear_action
    PRIVATE essence
)

set_target_properties(
    ethereal_golem
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
