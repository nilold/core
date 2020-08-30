add_executable(Organism_t Organism_t.cpp)
target_link_libraries(Organism_t
    PUBLIC
    gtest_main
)

add_executable(Bacteria_t Bacteria_t.cpp)
target_link_libraries(Bacteria_t
    PUBLIC
    gtest_main
)

gtest_discover_tests(Organism_t TEST_LIST OrganismTests)
gtest_discover_tests(Bacteria_t TEST_LIST BacteriaTests)

include_directories(${CMAKE_SOURCE_DIR}/src/include)