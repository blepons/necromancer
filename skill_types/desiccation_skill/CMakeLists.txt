add_library(
    desiccation_skill
    desiccation_skill.hpp desiccation_skill.cpp
)

target_include_directories(
    desiccation_skill
    INTERFACE .
)

target_link_libraries(
    desiccation_skill
    PUBLIC targeted_skill
    PRIVATE hero
    PRIVATE desiccation_action
)
