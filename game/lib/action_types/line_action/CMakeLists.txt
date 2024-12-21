add_library(
    line_action
    line_action.hpp line_action.cpp
)

target_include_directories(
    line_action
    INTERFACE .
)

target_link_libraries(
    line_action
    PUBLIC entity_action
    PRIVATE stage
    PRIVATE line
)
