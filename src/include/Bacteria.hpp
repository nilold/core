#pragma once

#include <Agent.hpp>
#include <Substract.hpp>

namespace core
{
    class Bacteria : public Agent
    {
        inline static std::string AGENT_TYPE{"Bacteria"};
        inline static int HEALTH{100};

    public:
        Bacteria(std::string name, int health = HEALTH);
        ~Bacteria() {}
        Bacteria(Bacteria &&o);
        Bacteria(const Bacteria &o) = delete;

        Bacteria &needs(nutrients::Minerals type, nutrients::quantity_t quantity);
        void cycle(Substract &substract) override;
        int getHealth() const;

    private:
        void takeResources(Substract &substract);

        std::string m_name{};
        unsigned hunger{};
        std::unordered_map<nutrients::Minerals, nutrients::quantity_t> m_needs;
    };
} // namespace core