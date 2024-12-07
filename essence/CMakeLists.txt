add_library(
    essence
    essence.hpp essence.cpp
)

target_include_directories(
    essence
    INTERFACE .
)

target_link_libraries(
    essence
    PUBLIC entity
    PRIVATE null_action
    PRIVATE hero
)
