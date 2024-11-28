add_library(
    targeted_skill
    targeted_skill.hpp targeted_skill.cpp
)

target_include_directories(
    targeted_skill
    INTERFACE .
)

target_link_libraries(
    targeted_skill
    PUBLIC usable_skill
    PUBLIC point
)
