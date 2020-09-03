add_library(Crops
    STATIC
    Crop.cpp
    Inffectable.cpp
)

target_include_directories(Crops PRIVATE ${CMAKE_SOURCE_DIR}/src/include)