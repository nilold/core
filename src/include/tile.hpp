#pragma once

#include <Substract.hpp>
#include <Crop.hpp>
#include <Agent.hpp>

#include <memory>

namespace core
{
    using CropPtr = std::shared_ptr<Crop>;

    class Tile: public Substract
    {
    public:
        Tile(unsigned x, unsigned y) : m_x{x}, m_y{y} {}
        ~Tile() = default;
        Tile(const Tile &) = delete;
        Tile(Tile &&tile) : m_x(tile.m_x), m_y(tile.m_y), m_crop(tile.m_crop) {}

        Tile &operator=(Tile &o) = delete;
        Tile &operator=(Tile &&o) = default;

        void setCrop(CropPtr &crop) { m_crop = crop; }
        CropPtr getCrop() { return m_crop; }

        bool contamine(std::shared_ptr<Agent> agent)
        {
            return m_crop ? m_crop->inffectWith(agent) : false;
        }

    private:
        unsigned m_x, m_y;
        CropPtr m_crop;
    };
} // namespace core