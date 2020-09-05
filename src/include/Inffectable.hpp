#pragma once

#include <Agent.hpp>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
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
        Inffectable(Inffectable &&rhs)
            : m_agents(std::move(rhs.m_agents)),
              m_agentPhylums(std::move(rhs.m_agentPhylums)),
              agentsResistance(std::move(rhs.agentsResistance)) {}

        bool inffectWith(AgentPtr a) noexcept;
        std::vector<AgentPtr> getAgents() { return m_agents; };

    protected:
        void addResistance(std::string agentType, int resistance);

    protected:
        std::vector<AgentPtr> m_agents{};

    private:
        bool infecctionSucceeds(AgentPtr a) const noexcept;
        bool hasResistance(const AgentPtr agentType) const noexcept;

    private:
        std::unordered_set<std::string> m_agentPhylums;
        std::unordered_map<std::string, int> agentsResistance;
    };
} // namespace core