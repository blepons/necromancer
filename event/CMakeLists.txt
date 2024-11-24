add_library(
    event
    INTERFACE
)

target_include_directories(
    event
    INTERFACE .
)

target_link_libraries(
    event
    INTERFACE point
)
