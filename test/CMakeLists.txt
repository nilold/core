add_executable(Organism_t Organism_t.cpp)
target_link_libraries(Organism_t
    PUBLIC
    gtest_main
)
# add_test(
#     NAME Organism_t
#     COMMAND Organism_t
# )

gtest_discover_tests(Organism_t TEST_LIST OrganismTests)

include_directories(${CMAKE_SOURCE_DIR}/src/include)