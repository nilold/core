#pragma once

#include <Agent.hpp>
#include <Organism.hpp>

namespace core
{
    class Bacteria : public Agent
    {
        inline static std::string AGENT_TYPE{"Bacteria"};
        inline static int HEALTH{100};

    public:
        Bacteria(std::string name, int health = HEALTH) : Agent("Bacteria", health), m_name(name) {}
        ~Bacteria() {}
        Bacteria(Bacteria &&o) : Agent(std::move(o)), m_name(o.m_name) {}
        Bacteria(const Bacteria &o) = delete;

        Bacteria &needs(nutrients::Minerals type, nutrients::quantity_t quantity)
        {
            m_needs[type] = quantity;
            return *this;
        }

        virtual void live(Organism &organism) override
        {
            takeResources(organism);
        }

        int getHealth() const
        {
            return m_health;
        }

    private:
        void takeResources(Organism &organism)
        {
            for (const auto &[mineral, required] : m_needs)
            {
                if (required == 0)
                    continue;
                auto aquired = organism.takeNutrient(mineral, required);
                m_health *= static_cast<double>(aquired) / required;
            }
        }
        std::string m_name{};
        unsigned hunger{};
        std::unordered_map<nutrients::Minerals, nutrients::quantity_t> m_needs;
    };
} // namespace core