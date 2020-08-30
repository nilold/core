#pragma once

// #include <Organism.hpp>
#include <string>
#include <unordered_map>

namespace core
{
    
    // namespace nutrients
    // {
        class Minerals;
        class quantity_t;
    // } // namespace nutrients
    class Organism;

    class Agent
    {
    public:
        Agent(std::string type, int health) : m_type{type}, m_health(health) {}
        virtual ~Agent(){};
        Agent(const Agent &) = delete;
        Agent(Agent &&a) : m_type(a.m_type) {}

        // virtual Organism &needs(Minerals type, quantity_t quantity) = 0;
        virtual void live(Organism &organism) = 0;

    protected:
        std::string m_type{};
        int m_health{};
        // std::unordered_map<Minerals, quantity_t> m_needs;
    };
} // namespace core