add_library(
    attack_action
    attack_action.hpp attack_action.cpp
)

target_include_directories(
    attack_action
    INTERFACE .
)

target_link_libraries(
    attack_action
    PUBLIC entity_action
)
