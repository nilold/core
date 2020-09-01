#pragma once

#include <string>
#include <unordered_map>

namespace core
{
    class Substract;

    class Agent
    {
    public:
        Agent(std::string type, int health) : m_type{type}, m_health(health) {}
        virtual ~Agent(){};
        Agent(const Agent &) = delete;
        Agent(Agent &&a) : m_type(a.m_type) {}

        virtual void activate(Substract &Substract) = 0;
        std::string type() const { return m_type; }

    protected:
        std::string m_type{};
        int m_health{};
    };
} // namespace core