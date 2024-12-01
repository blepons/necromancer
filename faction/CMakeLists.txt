add_library(
    faction
    faction.hpp faction.cpp
)

target_include_directories(
    faction
    INTERFACE .
)
