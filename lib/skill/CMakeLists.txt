add_library(
    skill
    skill.hpp skill.cpp
)

target_include_directories(
    skill
    INTERFACE .
)

target_link_libraries(
    skill
    PRIVATE hero
    PRIVATE skill_set
    PRIVATE serializable
)
