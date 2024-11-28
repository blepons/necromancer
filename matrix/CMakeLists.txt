cmake_minimum_required(VERSION 3.27)

project(matrix)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
)

add_library(
    matrix
    INTERFACE matrix.hpp
)

target_include_directories(
    matrix
    INTERFACE .
)

if(MATRIX_BUILD_TESTING)
    enable_testing()

    add_test(
        NAME TestMatrix
        COMMAND matrix_tests
    )
endif()

if(MATRIX_BUILD_TESTING)
    add_subdirectory(tests)
endif()
