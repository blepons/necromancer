add_library(
    leave_corpse_action
    leave_corpse_action.hpp leave_corpse_action.cpp
)

target_include_directories(
    leave_corpse_action
    INTERFACE .
)

target_link_libraries(
    leave_corpse_action
    PUBLIC entity_action
    PRIVATE corpse
    PRIVATE stage
)
