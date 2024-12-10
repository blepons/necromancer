add_library(
    energy
    energy.hpp energy.cpp
)

target_include_directories(
    energy
    INTERFACE .
)
