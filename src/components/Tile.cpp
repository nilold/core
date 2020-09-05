#include <Tile.hpp>
#include <Crop.hpp>

namespace core
{
    // Tile::Tile::Tile(Tile &&tile) : m_crop(tile.m_crop) {}

    void Tile::Tile::setCrop(CropPtr crop) { m_crop = crop; }
    CropPtr Tile::getCrop() const { return m_crop; }

    Tile &Tile::operator=(Tile &&rhs) noexcept
    {
        Substract::operator=(std::move(rhs));
        m_crop = std::move(rhs.m_crop);
        return *this;
    }

    bool Tile::contamine(std::shared_ptr<Agent> agent)
    {
        return m_crop ? m_crop->inffectWith(agent) : false;
    }
} // namespace core