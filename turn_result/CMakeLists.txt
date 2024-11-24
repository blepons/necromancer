add_library(
    turn_result
    INTERFACE
)

target_include_directories(
    turn_result
    INTERFACE .
)

target_link_libraries(
    turn_result
    INTERFACE event
)
