add_library(
    desiccation_action
    desiccation_action.hpp desiccation_action.cpp
)

target_include_directories(
    desiccation_action
    INTERFACE .
)

target_link_libraries(
    desiccation_action
    PUBLIC entity_action
    PRIVATE corpse
    PRIVATE hero
    PRIVATE heal_action
    PRIVATE mana_gain_action
)
