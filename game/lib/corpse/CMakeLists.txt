add_library(
    corpse
    corpse.hpp corpse.cpp
)

target_include_directories(
    corpse
    INTERFACE .
)

target_link_libraries(
    corpse
    PUBLIC entity
    PUBLIC attack
    PRIVATE do_nothing_action
    PRIVATE disappear_action
)
