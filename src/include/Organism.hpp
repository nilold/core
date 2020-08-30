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
        Organism() : Inffectable(), m_minerals(nutrients::M_COUNT, 0), m_vitamins(nutrients::V_COUNT, 0){};
        Organism(Organism &&o) : m_minerals(std::move(o.m_minerals)), m_vitamins(std::move(o.m_vitamins)) {}
        ~Organism() = default;

        Organism &withK(quantity_t quantity)
        {
            m_minerals[nutrients::Minerals::K] = 0;
            addMineral(nutrients::Minerals::K, quantity);
            return *this;
        }

        Organism &withNa(quantity_t quantity)
        {
            m_minerals[nutrients::Minerals::Na] = 0;
            addMineral(nutrients::Minerals::Na, quantity);
            return *this;
        }

        Organism &withFe(quantity_t quantity)
        {
            m_minerals[nutrients::Minerals::Fe] = 0;
            addMineral(nutrients::Minerals::Fe, quantity);
            return *this;
        }

        //TODO:: add others

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

        quantity_t getMineral(int type) const
        {
            if (!mineralTypeIsValid(type))
                return 0;
            return m_minerals[type];
        }

    private:
        std::vector<quantity_t> m_minerals;
        std::vector<quantity_t> m_vitamins;

        bool mineralTypeIsValid(int type) const
        {
            bool valid = type >= 0 && type < nutrients::M_COUNT;
            if (!valid)
                std::cerr << "Invalid mineral type: " << type << std::endl;
            return valid;
        }
    };
} // namespace core
