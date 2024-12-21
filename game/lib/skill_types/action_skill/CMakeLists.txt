add_library(
    action_skill
    action_skill.hpp action_skill.cpp
)

target_include_directories(
    action_skill
    INTERFACE .
)

target_link_libraries(
    action_skill
    PUBLIC usable_skill
)
