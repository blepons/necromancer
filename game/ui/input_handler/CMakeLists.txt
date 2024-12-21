add_library(
    input_handler
    input_handler.hpp input_handler.cpp
)

target_include_directories(
    input_handler
    INTERFACE .
)

target_link_libraries(
    input_handler
    PUBLIC game
    PUBLIC renderer
    PRIVATE direction
    PRIVATE hero
    PRIVATE targeted_skill
    PRIVATE corpse
)

