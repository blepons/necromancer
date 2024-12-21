add_library(
    disappear_action
    disappear_action.hpp disappear_action.cpp
)

target_include_directories(
    disappear_action
    INTERFACE .
)

target_link_libraries(
    disappear_action
    PUBLIC entity_action
    PRIVATE stage
)
