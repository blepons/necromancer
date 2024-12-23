add_library(
    polymorph_skill
    polymorph_skill.hpp polymorph_skill.cpp
)

target_include_directories(
    polymorph_skill
    INTERFACE .
)

target_link_libraries(
    polymorph_skill
    PUBLIC targeted_skill
    PRIVATE polymorph_action
    PRIVATE hero
)
