add_library(
    direction
    INTERFACE
)

target_include_directories(
    direction
    INTERFACE .
)

target_link_libraries(
    direction
    INTERFACE point
)
