add_library(
    entity_action
    entity_action.hpp entity_action.cpp
)

target_include_directories(
    entity_action
    INTERFACE .
)

target_link_libraries(
    entity_action
    PUBLIC action
    PUBLIC entity
)
