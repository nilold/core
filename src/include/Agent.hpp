#pragma once

#include <string>

namespace core
{
    class Agent
    {
    public:
        Agent(std::string name): m_name{name} {}
        ~Agent() = default;
        Agent(const Agent &) = delete;
        Agent(Agent && a): m_name(a.m_name){}

    private:
        std::string m_name{};
    };
} // namespace core