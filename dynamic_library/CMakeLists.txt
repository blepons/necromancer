add_library(
    dynamic_library
    dynamic_library.hpp dynamic_library.cpp
)

target_include_directories(
    dynamic_library
    INTERFACE .
)
