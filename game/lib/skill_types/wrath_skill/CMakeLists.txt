add_library(
    wrath_skill
    wrath_skill.hpp wrath_skill.cpp
)

target_include_directories(
    wrath_skill
    INTERFACE .
)

target_link_libraries(
    wrath_skill
    PUBLIC action_skill
    PRIVATE hero
    PRIVATE wrath_action
)
