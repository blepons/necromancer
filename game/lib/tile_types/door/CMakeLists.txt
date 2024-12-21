add_library(
    door
    door.hpp
)

target_include_directories(
    door
    INTERFACE .
)

add_subdirectory(closed_door)

add_subdirectory(open_door)

target_link_libraries(
    door
    PUBLIC closed_door
    PUBLIC open_door
)
