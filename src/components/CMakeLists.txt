add_library(Crops
    STATIC
    Crop.cpp
    Inffectable.cpp
)

add_library(Agents
    STATIC
    Bacteria.cpp
)

add_library(Field
    STATIC
    Tile.cpp
)

target_include_directories(Crops PRIVATE "${CMAKE_SOURCE_DIR}/src/include")
target_include_directories(Agents PRIVATE "${CMAKE_SOURCE_DIR}/src/include")
target_include_directories(Field PRIVATE "${CMAKE_SOURCE_DIR}/src/include")