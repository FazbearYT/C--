cmake_minimum_required(VERSION 3.16)
project(DataStructures CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Main App
add_executable(ds_app main.cpp)

# Tests
add_executable(ds_tests tests/test_main.cpp)

target_include_directories(ds_tests PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(ds_tests PRIVATE
    GTest::gtest
    GTest::gtest_main
)

enable_testing()
add_test(NAME AllTests COMMAND ds_tests)

# Code Coverage (LCOV)
option(COVERAGE "Enable code coverage" OFF)

if(COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Code Coverage Enabled (MinGW GCC)")

    # Extract the grandparent dir name (e.g. "lab4") to use as an lcov pattern.
    # Avoids two pitfalls: the C++ dir name contains '+' (Perl regex metachar),
    # and paths in .gcno files keep the original Windows casing from the build,
    # so patterns with lowercase drive/folder names never match.
    get_filename_component(SOURCE_PARENT_DIR "${CMAKE_SOURCE_DIR}" DIRECTORY)
    get_filename_component(LAB_DIR_NAME "${SOURCE_PARENT_DIR}" NAME)

    target_compile_options(ds_tests PRIVATE
        -fprofile-arcs
        -ftest-coverage
        -O0
        -g
        -fno-omit-frame-pointer
    )

    target_link_options(ds_tests PRIVATE
        -fprofile-arcs
        -ftest-coverage
    )

    add_custom_target(coverage
        DEPENDS ds_tests
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests..."
        COMMAND ./ds_tests.exe
        COMMAND ${CMAKE_COMMAND} -E echo "Capturing coverage data..."
        COMMAND lcov --capture --directory . --output-file coverage_total.info --rc lcov_branch_coverage=1
        COMMAND lcov --extract coverage_total.info "*${LAB_DIR_NAME}*" --output-file coverage_project.info
        COMMAND lcov --remove coverage_project.info "*_deps*" --output-file coverage.info
        COMMAND ${CMAKE_COMMAND} -E echo "Generating HTML report..."
        COMMAND genhtml coverage.info --output-directory coverage_report --rc genhtml_branch_coverage=1
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "LCOV report -> build/coverage_report/index.html"
    )
endif()
