#pragma once

#include <Agent.hpp>

#include <vector>
#include <string>
#include <memory>

namespace core
{
    using AgentPtr = std::shared_ptr<Agent>;

    class Inffectable
    {
    public:
        Inffectable() = default;
        ~Inffectable() = default;
        Inffectable(const Inffectable &) = delete;
        Inffectable(Inffectable &&inff) : m_agents(std::move(inff.m_agents)) {}

        bool tryInffection(AgentPtr a) noexcept;
        void suffer() noexcept;

    private:
        bool infecctionSucceeds(AgentPtr a) const noexcept;
        std::vector<AgentPtr> m_agents{};
    };
} // namespace core

namespace core
{
    bool Inffectable::tryInffection(AgentPtr a) noexcept
    {
        bool success = infecctionSucceeds(a);
        if (success)
        {
            m_agents.push_back(a);
        }
        return success;
    }

    bool Inffectable::infecctionSucceeds(AgentPtr a) const noexcept
    {
        return true;
    }

    void Inffectable::suffer() noexcept
    {

    }
} // namespace core