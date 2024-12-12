add_library(
    entity_builder
    entity_builder.hpp entity_builder.cpp
)

target_include_directories(
    entity_builder
    INTERFACE .
)

target_link_libraries(
    entity_builder
    PUBLIC entity
    PRIVATE game
    PRIVATE hero
    # TODO: remove temporary solution
    PRIVATE curse_skill
    PRIVATE necromancy_skill
    PRIVATE desiccation_skill
)

