#include <Bacteria.hpp>

namespace core
{
    Bacteria::Bacteria(std::string name, int health) : Agent("Bacteria", health), m_name(name) {}
    Bacteria::Bacteria(Bacteria &&o) : Agent(std::move(o)), m_name(o.m_name) {}

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