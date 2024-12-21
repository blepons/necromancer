add_library(
    heal_action
    heal_action.hpp heal_action.cpp
)

target_include_directories(
    heal_action
    INTERFACE .
)

target_link_libraries(
    heal_action
    PUBLIC entity_action
)
