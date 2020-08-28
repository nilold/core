cmake_minimum_required(VERSION 3.16)
project(farmer-core)

set(CMAKE_CXX_STANDARD 20)

add_executable(farmer 
    main.cpp 
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)