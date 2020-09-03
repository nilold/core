cmake_minimum_required(VERSION 3.17.0)
project(farmer-core)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/src/include)

add_subdirectory(src)

# Testing
enable_testing()
add_subdirectory(external/include/gtest)
include(GoogleTest)
add_subdirectory(test)