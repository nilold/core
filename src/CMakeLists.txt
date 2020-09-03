add_executable(farmer
    main.cpp
)

target_include_directories(farmer PRIVATE ${CMAKE_HOME_DIRECTORY}/src/include)

add_subdirectory(components)