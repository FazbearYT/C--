cmake_minimum_required(VERSION 3.16)
project(DataStructures CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#Main App
add_executable(ds_app main.cpp)

#Tests
add_executable(ds_tests tests/test_main.cpp)

target_include_directories(ds_tests PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(ds_tests PRIVATE 
    GTest::gtest 
    GTest::gtest_main
)

set_source_files_properties(stack.cpp queue.cpp bst.cpp 
    PROPERTIES HEADER_FILE_ONLY TRUE)

enable_testing()
add_test(NAME AllTests COMMAND ds_tests)

#CODE COVERAGE (LCOV)
option(COVERAGE "Enable code coverage" OFF)

if(COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Code Coverage Enabled (MinGW)")
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0 -g -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

    target_compile_options(ds_tests PRIVATE 
        -fprofile-arcs 
        -ftest-coverage 
        -O0 
        -g
    )
    
    target_link_options(ds_tests PRIVATE 
        -fprofile-arcs 
        -ftest-coverage
    )

    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests for coverage..."
        COMMAND ./ds_tests.exe
        
        COMMAND ${CMAKE_COMMAND} -E make_directory coverage_report
        
        COMMAND lcov --capture --directory . --output-file coverage_report/coverage.info --rc lcov_branch_coverage=1 --no-external --ignore-errors source
        COMMAND lcov --remove coverage_report/coverage.info '/usr/*' '*/_deps/*' '*/googletest/*' '*/tests/*' --output-file coverage_report/coverage.info
        COMMAND genhtml coverage_report/coverage.info --output-directory coverage_report/html --rc genhtml_branch_coverage=1
        
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating LCOV report..."
    )
endif()