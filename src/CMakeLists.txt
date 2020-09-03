add_executable(farmer
    main.cpp
)

target_include_directories(farmer PRIVATE ${INCLUDES_DIR})
add_subdirectory(components)