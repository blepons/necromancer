add_library(
    do_nothing_action
    do_nothing_action.hpp do_nothing_action.cpp
)

target_include_directories(
    do_nothing_action
    INTERFACE .
)

target_link_libraries(
    do_nothing_action
    PUBLIC entity_action
)
