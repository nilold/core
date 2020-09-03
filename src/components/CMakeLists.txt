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

set(INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/../src/include)

target_include_directories(Crops PRIVATE ${INCLUDES_DIR})
target_include_directories(Agents PRIVATE ${INCLUDES_DIR})
target_include_directories(Field PRIVATE ${INCLUDES_DIR})