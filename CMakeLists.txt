cmake_minimum_required(VERSION 3.17.3)
project(farmer-core)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

# Testing
enable_testing()
add_subdirectory(external/include/googletest)
include(GoogleTest)
add_subdirectory(test)
