find_package(Catch2 3 REQUIRED)

add_executable(
    matrix_tests
    matrix_tests.cpp
)

target_link_libraries(
    matrix_tests
    PRIVATE matrix
    PRIVATE Catch2::Catch2WithMain
)

add_test(
    NAME TestMatrix
    COMMAND matrix_tests
)
