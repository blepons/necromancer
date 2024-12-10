add_library(
    skill_set
    skill_set.hpp skill_set.cpp
)

target_include_directories(
    skill_set
    INTERFACE .
)
