add_executable(farmer
    main.cpp
)

set(INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/../src/include)
target_include_directories(farmer PRIVATE ${INCLUDES_DIR})
add_subdirectory(components)