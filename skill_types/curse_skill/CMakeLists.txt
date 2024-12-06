add_library(
    curse_skill
    curse_skill.hpp curse_skill.cpp
)

target_include_directories(
    curse_skill
    INTERFACE .
)

target_link_libraries(
    curse_skill
    PUBLIC targeted_skill
    PRIVATE bolt_attack_action
    PRIVATE hero
)
