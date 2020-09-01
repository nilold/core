#pragma once

#include <Agent.hpp>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <cstdlib>

namespace core
{
    using AgentPtr = std::shared_ptr<Agent>;

    class Inffectable
    {
    public:
        Inffectable() = default;
        ~Inffectable() = default;
        Inffectable(const Inffectable &) = delete;
        Inffectable(Inffectable &&inff)
            : m_agents(std::move(inff.m_agents)),
              agentsResistance(std::move(inff.agentsResistance)) {}

        bool inffectWith(AgentPtr a) noexcept;

    protected:
        void addResistance(std::string agentType, int resistance)
        {
            agentsResistance[agentType] += resistance;
        }
        //TODO:: resistances should degrade with time

    protected:
        std::vector<AgentPtr> m_agents{};

    private:
        bool infecctionSucceeds(AgentPtr a) const noexcept;
        bool hasResistance(const AgentPtr agentType) const noexcept;

    private:
        std::unordered_map<std::string, int> agentsResistance;
    };
} // namespace core

namespace core
{
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
