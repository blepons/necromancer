add_library(
    undead_registry
    undead_registry.hpp undead_registry.cpp
)

target_include_directories(
    undead_registry
    INTERFACE .
)

target_link_libraries(
    undead_registry
    PUBLIC undead
)
