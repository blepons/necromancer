cmake_minimum_required(VERSION 3.27)

project(necromancer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
)

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_subdirectory(action)

add_subdirectory(action_types)

add_subdirectory(api)

add_subdirectory(attack)

add_subdirectory(cost_priority_queue)

add_subdirectory(direction)

add_subdirectory(dynamic_library)

add_subdirectory(energy)

add_subdirectory(entity)

add_subdirectory(event)

add_subdirectory(faction)

add_subdirectory(fov)

add_subdirectory(game)

add_subdirectory(geometry)

add_subdirectory(hero)

add_subdirectory(library_manager)

add_subdirectory(matrix)

add_subdirectory(mob)

add_subdirectory(mob_state)

add_subdirectory(mob_state_types)

add_subdirectory(move)

add_subdirectory(passability)

add_subdirectory(pathfinder)

add_subdirectory(plugin_keeper)

add_subdirectory(plugin_manager)

add_subdirectory(point)

add_subdirectory(skill)

add_subdirectory(skill_set)

add_subdirectory(skill_types)

add_subdirectory(stage)

add_subdirectory(tile)

add_subdirectory(turn_result)
