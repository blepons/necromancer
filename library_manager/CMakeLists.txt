add_library(
    library_manager
    library_manager.hpp library_manager.cpp
)

target_include_directories(
    library_manager
    INTERFACE .
)

target_link_libraries(
    library_manager
    PUBLIC dynamic_library
    PUBLIC mob_plugin
)
