add_library(
    mob
    mob.hpp mob.cpp
)

target_include_directories(
    mob
    INTERFACE .
)

target_link_libraries(
    mob
    PUBLIC entity
    PUBLIC attack
    PUBLIC move
    PRIVATE mob_state
    PRIVATE asleep_state
)
