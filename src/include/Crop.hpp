#pragma once

#include <Substract.hpp>
#include <Inffectable.hpp>

namespace core
{
    class Crop : public Substract, public Inffectable
    {
    public:
        Crop(std::string specie, int health = 100, int maxHealth = 100)
            : Substract(), Inffectable(), m_specie{specie}, m_health{health}, m_maxHealth{maxHealth} {}
        Crop(const Crop &c) = delete;
        Crop(Crop &&c) // TODO: is this right?
            : Substract(std::move(c)),
              Inffectable(std::move(c)),
              m_specie(c.m_specie), m_health(c.m_health), m_maxHealth(c.m_maxHealth), m_needs{c.m_needs}
        {
        }
        ~Crop() = default;

        int health() { return m_health; }
        std::string specie() { return m_specie; }
        void setSpecie(const std::string &specie) { m_specie = specie; }

        void cycle()
        {
            activateAgents();
            updateHealth();
        }

        Crop &needs(nutrients::Minerals type, nutrients::quantity_t quantity)
        {
            m_needs[type] = quantity;
            return *this;
        }

    private:
        void activateAgents()
        {
            for (auto agent : m_agents)
            {
                agent->activate(*this);
            }
        }

        void updateHealth()
        {
            for (const auto &[neededMineral, neededQuantity] : m_needs)
            {
                double healthRatio = static_cast<double>(getNutrient(neededMineral)) / neededQuantity;
                m_health *= healthRatio;
                if (m_health > m_maxHealth)
                    m_health = m_maxHealth;
            }
        }

    private:
        std::string m_specie{};
        int m_health{};
        int m_maxHealth{};
        std::unordered_map<nutrients::Minerals, nutrients::quantity_t> m_needs;
    };
} // namespace core

namespace core
{

} // namespace core
