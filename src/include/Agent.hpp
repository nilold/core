#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace core
{
    class Substract;

    class Agent
    {
    public:
        Agent(std::string type, std::string phylum, int health)
            : m_type{type}, m_phylum{phylum}, m_health(health) {}
        virtual ~Agent(){};
        Agent(const Agent &) = delete;
        Agent(Agent &&a) : m_type(a.m_type) {}

        virtual void cycle(Substract &Substract) = 0;

        int health() const { return m_health; }
        std::string type() const { return m_type; }
        std::string phylum() const { return m_phylum; }
        virtual std::shared_ptr<Agent> selfCopy() const = 0;

    protected:
        std::string m_type{};
        std::string m_phylum{};
        int m_health{};
    };
} // namespace core