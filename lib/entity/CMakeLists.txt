add_library(
    entity
    entity.hpp entity.cpp
)

target_include_directories(
    entity
    INTERFACE .
)

target_link_libraries(
    entity
    PUBLIC energy
    PUBLIC fov
    PRIVATE stage
    PRIVATE action
    PUBLIC passability
    PUBLIC point
    PUBLIC faction
    PUBLIC serializable
)
