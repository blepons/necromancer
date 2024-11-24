add_library(
    mob
    mob.hpp mob.cpp
)

target_include_directories(
    mob
    INTERFACE .
)

target_link_libraries(
    mob
    PUBLIC entity
    
)
