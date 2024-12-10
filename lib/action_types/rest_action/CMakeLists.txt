add_library(
    rest_action
    rest_action.hpp rest_action.cpp
)

target_include_directories(
    rest_action
    INTERFACE .
)

target_link_libraries(
    rest_action
    PUBLIC entity_action
    PRIVATE hero
    PRIVATE stage
)
