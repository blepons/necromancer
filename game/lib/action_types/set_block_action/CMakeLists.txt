add_library(
    set_block_action
    set_block_action.hpp set_block_action.cpp
)

target_include_directories(
    set_block_action
    INTERFACE .
)

target_link_libraries(
    set_block_action
    PUBLIC entity_action
)
