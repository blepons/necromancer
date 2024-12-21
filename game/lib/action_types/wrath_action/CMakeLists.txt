add_library(
    wrath_action
    wrath_action.hpp wrath_action.cpp
)

target_include_directories(
    wrath_action
    INTERFACE .
)

target_link_libraries(
    wrath_action
    PUBLIC entity_action
)
