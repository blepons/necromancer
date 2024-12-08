add_library(
    necromancy_skill
    necromancy_skill.hpp necromancy_skill.cpp
)

target_include_directories(
    necromancy_skill
    INTERFACE .
)

target_link_libraries(
    necromancy_skill
    PUBLIC targeted_skill
    PRIVATE necromancy_action
    PRIVATE hero
)
