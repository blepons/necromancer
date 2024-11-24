add_library(
    mana_action
    mana_action.hpp mana_action.cpp
)

target_include_directories(
    mana_action
    INTERFACE .
)

target_link_libraries(
    mana_action
    PUBLIC entity_action
    PRIVATE hero
)
