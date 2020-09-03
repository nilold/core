#pragma once

#include <Substract.hpp>
#include <Crop.hpp>
#include <Agent.hpp>

#include <memory>

namespace core
{
    using CropPtr = std::shared_ptr<Crop>;

    class Tile : public Substract
    {
    public:
        Tile(unsigned x, unsigned y);
        ~Tile() = default;
        Tile(const Tile &) = delete;
        Tile(Tile &&tile);

        Tile &operator=(Tile &o) = delete;
        Tile &operator=(Tile &&o) = default;

        void setCrop(CropPtr &crop);
        CropPtr getCrop() const;
        bool contamine(std::shared_ptr<Agent> agent);

    private:
        unsigned m_x, m_y;
        CropPtr m_crop;
    };
} // namespace core