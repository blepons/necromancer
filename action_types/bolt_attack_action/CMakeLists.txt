add_library(
    bolt_attack_action
    bolt_attack_action.hpp bolt_attack_action.cpp
)

target_include_directories(
    bolt_attack_action
    INTERFACE .
)

target_link_libraries(
    bolt_attack_action
    PUBLIC line_action
    # PRIVATE stage
)
