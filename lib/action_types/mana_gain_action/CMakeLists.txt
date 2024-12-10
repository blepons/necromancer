add_library(
    mana_gain_action
    mana_gain_action.hpp mana_gain_action.cpp
)

target_include_directories(
    mana_gain_action
    INTERFACE .
)

target_link_libraries(
    mana_gain_action
    PUBLIC entity_action
    PRIVATE hero
)
