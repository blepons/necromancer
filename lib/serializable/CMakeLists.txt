add_library(
    serializable
    INTERFACE serializable.hpp
)

target_include_directories(
    serializable
    INTERFACE .
)

target_link_libraries(
    serializable
    INTERFACE nlohmann_json::nlohmann_json
)
