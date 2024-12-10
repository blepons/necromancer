add_library(
    lava_burn_action
    lava_burn_action.hpp lava_burn_action.cpp
)

target_include_directories(
    lava_burn_action
    INTERFACE .
)

target_link_libraries(
    lava_burn_action
    PUBLIC action
    PRIVATE stage
)
