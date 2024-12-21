add_library(
    usable_skill
    usable_skill.hpp usable_skill.cpp
)

target_include_directories(
    usable_skill
    INTERFACE .
)

target_link_libraries(
    usable_skill
    PUBLIC skill
    PUBLIC mana_action
)
