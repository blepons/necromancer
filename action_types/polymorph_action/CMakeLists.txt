add_library(
    polymorph_action
    polymorph_action.hpp polymorph_action.cpp
)

target_include_directories(
    polymorph_action
    INTERFACE .
)
