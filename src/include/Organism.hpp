#pragma once

#include <Inffectable.hpp>

#include <vector>
#include <iostream>

namespace core
{
    using quantity_t = int;

    namespace nutrients
    {
        enum Minerals
        {
            K,
            Na,
            Fe,
            N,
            M_COUNT
        };

        enum Vitamins
        {
            A,
            B,
            C,
            V_COUNT
        };
    } // namespace nutrients

    class Organism : public Inffectable
    {

    public:
        Organism() : Inffectable(), m_minerals(nutrients::M_COUNT), m_vitamins(nutrients::V_COUNT){};
        Organism(Organism &&o) : m_minerals(std::move(o.m_minerals)), m_vitamins(std::move(o.m_vitamins)) {}
        ~Organism() = default;

        void addMineral(int type, quantity_t quantity) //TODO: think about quantities vs concentration
        {
            if (mineralTypeIsValid(type))
                m_minerals[type] += quantity;
        }

        quantity_t takeMineral(int type, quantity_t quantity)
        {
            if (!mineralTypeIsValid(type))
                return 0;

            if (m_minerals[type] > quantity)
            {
                m_minerals[type] -= quantity;
            }
            else
            {
                quantity = m_minerals[type];
                m_minerals[type] = 0;
            }
            return quantity;
        }

    private:
        std::vector<quantity_t> m_minerals;
        std::vector<quantity_t> m_vitamins;

        bool mineralTypeIsValid(int type)
        {
            bool valid = type >= 0 && type < nutrients::M_COUNT;
            if (!valid)
                std::cerr << "Invalid mineral type: " << type << std::endl;
            return valid;
        }
    };
} // namespace core
