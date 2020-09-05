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
        using pos_t = int;

    public:
        Field(int size_x, int size_y)
            : m_size_x{size_x},
              m_size_y{size_y}
        {
            assert(size_x > 0 && size_y > 0);
            buildField();
        }
        Field(const Field &field) = delete;

        void spreadAgents()
        {
            std::vector<std::vector<std::vector<AgentPtr>>> contamined(m_size_x, std::vector<std::vector<AgentPtr>>(m_size_y));
            for (pos_t x = 0; x < m_size_x; ++x)
            {
                for (pos_t y = 0; y < m_size_y; ++y)
                {
                    auto cropPtr = m_tiles[x][y]->getCrop();
                    if (!cropPtr)
                        continue;

                    pos_t rightX = x + 1;
                    pos_t leftX = x - 1;
                    pos_t upperY = y - 1;
                    pos_t downY = y + 1;

                    bool goRight = rightX < m_size_x;
                    bool goLeft = leftX >= 0;
                    bool goUp = upperY >= 0;
                    bool goDown = downY < m_size_y;

                    for (auto agentPtr : cropPtr->getAgents())
                    {
                        if (goRight)
                            contamined[rightX][y].emplace_back(agentPtr->selfCopy());
                        if (goLeft)
                            contamined[leftX][y].emplace_back(agentPtr->selfCopy());
                        if (goUp)
                            contamined[x][upperY].emplace_back(agentPtr->selfCopy());
                        if (goDown)
                            contamined[x][downY].emplace_back(agentPtr->selfCopy());
                    }
                }
            }

            for (pos_t x = 0; x < m_size_x; ++x)
            {
                for (pos_t y = 0; y < m_size_y; ++y)
                {
                    for(auto agentptr : contamined[x][y])
                    {
                        m_tiles[x][y]->getCrop()->inffectWith(agentptr);
                    }
                }
            }
        }

        void setCropToTile(std::shared_ptr<Crop> crop, pos_t posX, pos_t posY) noexcept
        {
            if (posX < m_size_x && posY < m_size_y)
                m_tiles[posX][posY]->setCrop(crop);
        }

        std::shared_ptr<Crop> getCrop(pos_t posX, pos_t posY) const
        {
            return m_tiles[posX][posY]->getCrop();
        }

    private:
        void buildField()
        {
            m_tiles.reserve(m_size_x);
            for (int x = 0; x < m_size_x; ++x)
            {
                m_tiles.emplace(m_tiles.begin() + x);
                m_tiles[x].reserve(m_size_y);
                for (int y = 0; y < m_size_y; ++y)
                {
                    m_tiles[x].emplace(m_tiles[x].begin() + y, std::make_unique<Tile>());
                }
            }
        }

    private:
        int m_size_x{};
        int m_size_y{};
        tileMatrix_t m_tiles;
    };
} // namespace core