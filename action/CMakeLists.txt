add_library(
    action
    action.hpp action.cpp
)

target_include_directories(
    action
    INTERFACE .
)

target_link_libraries(
    action
    PUBLIC event
    PUBLIC game
    PRIVATE entity
    # INTERFACE point
)
