#pragma once

#include <Substract.hpp>
#include <Inffectable.hpp>

namespace core
{
    using health_t = std::int_fast8_t;

    class Crop : public Substract, public Inffectable
    {
    public:
        Crop(
            std::string specie,
            health_t health = 100,
            health_t maxHealth = 100,
            health_t healthDevelopThreshold = 50,
            std::int_fast8_t cyclesPerStage = 10)
            : Substract(), Inffectable(),
              m_specie{specie},
              m_health{health},
              m_maxHealth{maxHealth},
              m_healthDevelopThreshold{healthDevelopThreshold},
              m_cyclesPerStage{cyclesPerStage}
        {
        }
        Crop(const Crop &c) = delete;
        Crop(Crop &&c) // TODO: is this right?
            : Substract(std::move(c)),
              Inffectable(std::move(c)),
              m_specie(c.m_specie),
              m_health(c.m_health),
              m_maxHealth(c.m_maxHealth),
              m_healthDevelopThreshold(c.m_healthDevelopThreshold),
              m_needs{c.m_needs},
              m_cyclesPerStage{c.m_cyclesPerStage},
              m_stageCycles{c.m_stageCycles},
              m_stage{c.m_stage}
        {
        }
        ~Crop() = default;

        health_t health() const { return m_health; }
        std::int_fast8_t phenologicalStage() const { return m_stage; }
        std::string specie() const { return m_specie; }
        void setSpecie(const std::string &specie) { m_specie = specie; }

        void cycle()
        {
            develop();
            cycleAgents();
            updateHealth();
        }

        Crop &needs(nutrients::Minerals type, nutrients::quantity_t quantity)
        {
            m_needs[type] = quantity;
            return *this;
        }

    private:
        void develop()
        {
            if (m_health >= m_healthDevelopThreshold)
                ++m_stageCycles;

            if (m_stageCycles >= m_cyclesPerStage)
            {
                m_stageCycles = 0;
                ++m_stage;
            }
        }

        void cycleAgents()
        {
            for (auto agent : m_agents)
            {
                agent->cycle(*this);
            }
        }

        void updateHealth()
        {
            for (const auto &[neededMineral, neededQuantity] : m_needs)
            {
                double healthRatio = static_cast<double>(getNutrient(neededMineral)) / neededQuantity;
                auto newHealth = static_cast<std::uint_fast32_t>(m_health * healthRatio);
                m_health = newHealth > m_maxHealth ? m_maxHealth : newHealth;
            }
        }

    private:
        std::string m_specie{};
        health_t m_health{};
        health_t m_maxHealth{};
        health_t m_healthDevelopThreshold{};
        std::int_fast8_t m_cyclesPerStage{};
        std::int_fast8_t m_stageCycles{0};
        std::int_fast8_t m_stage{0};
        std::unordered_map<nutrients::Minerals, nutrients::quantity_t> m_needs;
    };
} // namespace core

namespace core
{

} // namespace core
