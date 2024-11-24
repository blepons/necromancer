add_library(
    line
    INTERFACE
)

target_include_directories(
    line
    INTERFACE .
)

target_link_libraries(
    line
    INTERFACE point
)
