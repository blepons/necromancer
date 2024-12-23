add_library(
    attack
    attack.hpp attack.cpp
)

target_include_directories(
    attack
    INTERFACE .
)

target_link_libraries(
    attack
    PUBLIC serializable
    PRIVATE entity
)
