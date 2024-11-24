add_library(
    hero
    hero.hpp hero.cpp
)

target_include_directories(
    hero
    INTERFACE .
)

target_link_libraries(
    hero
    PUBLIC entity
    PUBLIC skill_set
)
