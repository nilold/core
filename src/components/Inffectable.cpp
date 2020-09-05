#include <Inffectable.hpp>

namespace core
{
    void Inffectable::addResistance(std::string agentType, int resistance)
    {
        agentsResistance[agentType] += resistance;
        //TODO:: resistances should degrade with time
    }

    bool Inffectable::inffectWith(AgentPtr a) noexcept
    {
        bool success = infecctionSucceeds(a);
        if (success)
        {
            m_agents.insert(a);
            m_agentPhylums.insert(a->phylum());
        }
        return success;
    }

    bool Inffectable::contains(AgentPtr agent) const noexcept
    {
        return m_agentPhylums.find(agent->phylum()) != m_agentPhylums.end();
    }

    bool Inffectable::infecctionSucceeds(AgentPtr agent) const noexcept
    {
        if (contains(agent))
            return false;

        int resistance = hasResistance(agent) ? agentsResistance.at(agent->type()) : 0;
        return std::rand() > resistance;
    }

    bool Inffectable::hasResistance(const AgentPtr agentType) const noexcept
    {
        return agentsResistance.find(agentType->type()) != agentsResistance.end();
    }

    void Inffectable::removeAgent(AgentPtr agent)
    {
        // static_cast<void>(std::remove(m_agents.begin(), m_agents.end(), agent));
        m_agents.erase(agent);
        m_agentPhylums.erase(agent->phylum());
    }
} // namespace core