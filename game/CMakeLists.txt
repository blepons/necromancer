cmake_minimum_required(VERSION 3.28)
project(game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
    main
    main.cpp
)

target_link_libraries(
    main
    PRIVATE game
    PRIVATE json_floor_manager
    PRIVATE wall
    PRIVATE floor
    PRIVATE lava
    PRIVATE renderer
    PRIVATE input_handler
    PRIVATE library_manager
    PRIVATE stairs
)

target_compile_features(
    main
    PRIVATE cxx_std_17
)

add_subdirectory(lib)

add_subdirectory(ui)

add_subdirectory(loading)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
