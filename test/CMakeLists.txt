add_executable(Substract_t Substract_t.cpp)
target_link_libraries(Substract_t
    PUBLIC
    gtest_main
)
target_include_directories(Substract_t PRIVATE "${CMAKE_HOME_DIRECTORY}/src/include")


add_executable(Bacteria_t Bacteria_t.cpp)
target_link_libraries(Bacteria_t
    PUBLIC
    gtest_main
    Agents
)
target_include_directories(Bacteria_t PRIVATE "${CMAKE_HOME_DIRECTORY}/src/include")

add_executable(Crop_t Crop_t.cpp)
target_link_libraries(Crop_t
    PUBLIC
    gtest_main
    Crops
    Agents
)

target_include_directories(Crop_t PRIVATE "${CMAKE_HOME_DIRECTORY}/src/include")

gtest_discover_tests(Substract_t TEST_LIST SubstractTests)
gtest_discover_tests(Bacteria_t TEST_LIST BacteriaTests)
gtest_discover_tests(Crop_t TEST_LIST CropTests)

# include_directories(${CMAKE_SOURCE_DIR}/src/include)