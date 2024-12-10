add_library(
    event
    INTERFACE event.hpp
)

target_include_directories(
    event
    INTERFACE .
)

target_link_libraries(
    event
    INTERFACE point
)
