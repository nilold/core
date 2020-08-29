#include <Tile.hpp>
#include <Agent.hpp>
#include <Crop.hpp>

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char *argv[])
{
    std::cout << "Hello, World!\n";

    std::vector<std::vector<core::Tile>> field(1);
    field[0].emplace_back(core::Tile(0,0));

    auto crop1 = std::make_shared<core::Crop>("Beans");
    field[0][0].setCrop(crop1);

    auto agent1 = std::make_shared<core::Agent>("Fungus");
    auto agent2 = std::make_shared<core::Agent>("Bacteria");

    std::cout << field[0][0].contamine(agent1);
    std::cout << field[0][0].contamine(agent2);
    return 0;
}