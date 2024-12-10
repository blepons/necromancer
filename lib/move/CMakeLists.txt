add_library(
    move
    move.hpp move.cpp
)

target_include_directories(
    move
    INTERFACE .
)

target_link_libraries(
    move
    PUBLIC action
    PRIVATE mob
)
