add_library(
    null_action
    null_action.hpp null_action.cpp
)

target_include_directories(
    null_action
    INTERFACE .
)

target_link_libraries(
    null_action
    PUBLIC action
)
