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
        Tile() = default;
        ~Tile() = default;
        Tile(const Tile &) = delete;
        Tile(Tile &&tile) = default;

        Tile &operator=(Tile &rhs) = delete;
        Tile &operator=(Tile &&rhs) noexcept;

        void setCrop(CropPtr crop);
        CropPtr getCrop() const;
        bool contamine(std::shared_ptr<Agent> agent);

    private:
        CropPtr m_crop;
    };
} // namespace core