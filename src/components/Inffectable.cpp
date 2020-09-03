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
            m_agents.push_back(a);
        }
        return success;
    }

    bool Inffectable::infecctionSucceeds(AgentPtr agent) const noexcept
    {
        int resistance = hasResistance(agent) ? agentsResistance.at(agent->type()) : 0;
        return std::rand() > resistance;
    }

    bool Inffectable::hasResistance(const AgentPtr agentType) const noexcept
    {
        return agentsResistance.find(agentType->type()) != agentsResistance.end();
    }
} // namespace core