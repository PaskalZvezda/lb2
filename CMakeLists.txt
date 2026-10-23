cmake_minimum_required(VERSION 3.14)

project(ip_filter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ip_filter ip_filter.cpp)

add_executable(test_ip_filter test_ip_filter.cpp)
target_compile_definitions(test_ip_filter PRIVATE UNIT_TEST)
target_link_libraries(test_ip_filter PRIVATE GTest::gtest_main)

enable_testing()
add_test(NAME test_ip_filter COMMAND test_ip_filter)
