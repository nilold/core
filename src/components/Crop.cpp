#include <Crop.hpp>

namespace core
{
    Crop::Crop(
        std::string specie,
        health_t health,
        health_t maxHealth,
        health_t healthDevelopThreshold,
        std::int_fast8_t cyclesPerStage)
        : Substract(), Inffectable(),
          m_specie{specie},
          m_health{health},
          m_maxHealth{maxHealth},
          m_healthDevelopThreshold{healthDevelopThreshold},
          m_cyclesPerStage{cyclesPerStage}
    {
    }

    Crop::Crop(Crop &&c) noexcept
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

    health_t Crop::health() const { return m_health; }
    std::int_fast8_t Crop::phenologicalStage() const { return m_stage; }
    std::string Crop::specie() const { return m_specie; }
    void Crop::setSpecie(const std::string &specie) { m_specie = specie; }

    void Crop::cycle()
    {
        develop();
        cycleAgents();
        updateHealth();
    }

    Crop &Crop::needs(nutrients::Minerals type, nutrients::quantity_t quantity)
    {
        m_needs[type] = quantity;
        return *this;
    }

    void Crop::develop()
    {
        if (m_health >= m_healthDevelopThreshold)
            ++m_stageCycles;

        if (m_stageCycles >= m_cyclesPerStage)
        {
            m_stageCycles = 0;
            ++m_stage;
        }
    }

    void Crop::cycleAgents()
    {
        std::vector<AgentPtr> deadAgents;
        for (auto agent : m_agents)
        {
            agent->cycle(*this);
            if(agent->health() <= 0)
                deadAgents.push_back(agent);
        }

        for(auto deadAgent: deadAgents)
            removeAgent(deadAgent);
    }

    void Crop::updateHealth()
    {
        for (const auto &[neededMineral, neededQuantity] : m_needs)
        {
            double healthRatio = static_cast<double>(getNutrient(neededMineral)) / neededQuantity;
            auto newHealth = static_cast<std::uint_fast32_t>(m_health * healthRatio);
            m_health = newHealth > m_maxHealth ? m_maxHealth : newHealth;
        }
    }

} // namespace core