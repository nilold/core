#pragma once
#include <Tile.hpp>
#include <Agent.hpp>

#include <vector>
#include <unordered_map>
#include <cassert>
#include <memory>

namespace core
{
    class Field
    {
        using tileMatrix_t = std::vector<std::vector<std::unique_ptr<Tile>>>;
        using targets_t = std::vector<std::vector<std::vector<AgentPtr>>>;
        using pos_t = int;

    public:
        Field(int size_x, int size_y);
        Field(const Field &field) = delete;

        void spreadAgents();
        void setCropToTile(std::shared_ptr<Crop> crop, pos_t posX, pos_t posY) noexcept;
        std::shared_ptr<Crop> getCrop(pos_t posX, pos_t posY) const;

    private:
        void buildField();
        void contamineCrops(targets_t contamined);
        bool positionIsValid(pos_t posX, pos_t posY) const noexcept;

    private:
        int m_size_x{};
        int m_size_y{};
        tileMatrix_t m_tiles;
    };
} // namespace core