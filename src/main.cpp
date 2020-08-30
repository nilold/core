#include <Tile.hpp>
#include <Bacteria.hpp>
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
    crop1->withK(100).withNa(100).withFe(100);
    field[0][0].setCrop(crop1);

    auto agent1 = std::make_shared<core::Bacteria>("bac1");
    auto agent2 = std::make_shared<core::Bacteria>("bac2");

    std::cout << field[0][0].contamine(agent1);
    std::cout << field[0][0].contamine(agent2);
    return 0;
}