#include <Bacteria.hpp>

namespace core
{
    Bacteria::Bacteria(std::string phylum, int health) : Agent(AGENT_TYPE, phylum, health) {}
    Bacteria::Bacteria(Bacteria &&o) : Agent(std::move(o)) {}

    Bacteria &Bacteria::needs(nutrients::Minerals type, nutrients::quantity_t quantity)
    {
        m_needs[type] = quantity;
        return *this;
    }

    void Bacteria::cycle(Substract &substract)
    {
        takeResources(substract);
    }

    int Bacteria::getHealth() const
    {
        return m_health;
    }

    std::shared_ptr<Agent> Bacteria::selfCopy() const
    {
        //should health be restored on copy?
        auto cpy = std::make_shared<Bacteria>(m_phylum, m_health);
        cpy->m_needs = m_needs;
        return cpy;
    }

    void Bacteria::takeResources(Substract &substract)
    {
        for (const auto &[mineral, required] : m_needs)
        {
            if (required == 0)
                continue;
            auto acquired = substract.takeNutrient(mineral, required);
            m_health *= static_cast<double>(acquired) / required;
        }
    }
} // namespace core