#include <Tile.hpp>

namespace core
{
    Tile::Tile(unsigned x, unsigned y) : m_x{x}, m_y{y} {}
    Tile::Tile::Tile(Tile &&tile) : m_x(tile.m_x), m_y(tile.m_y), m_crop(tile.m_crop) {}

    void Tile::Tile::setCrop(CropPtr &crop) { m_crop = crop; }
    CropPtr Tile::getCrop() const { return m_crop; }

    bool Tile::contamine(std::shared_ptr<Agent> agent)
    {
        return m_crop ? m_crop->inffectWith(agent) : false;
    }
} // namespace core