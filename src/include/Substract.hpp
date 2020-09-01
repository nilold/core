#pragma once

#include <vector>
#include <iostream>

namespace core
{
    namespace nutrients
    {
        using quantity_t = int;

        enum class Minerals
        {
            K,
            Na,
            Fe,
            N,
            COUNT
        };

        enum class Vitamins
        {
            A,
            B,
            C,
            COUNT
        };

    } // namespace nutrients

    using nutrients::quantity_t;

    class Substract
    {

    public:
        Substract() : m_minerals(static_cast<int>(nutrients::Minerals::COUNT)),
                     m_vitamins(static_cast<int>(nutrients::Vitamins::COUNT)){};
        Substract(Substract &&o) : m_minerals(std::move(o.m_minerals)), m_vitamins(std::move(o.m_vitamins)) {}
        ~Substract() = default;
        Substract(const Substract &o) = delete;

        Substract &withK(quantity_t quantity)
        {
            (*this)[nutrients::Minerals::K] = quantity;
            return *this;
        }

        Substract &withNa(quantity_t quantity)
        {
            (*this)[nutrients::Minerals::Na] = quantity;
            return *this;
        }

        Substract &withFe(quantity_t quantity)
        {
            (*this)[nutrients::Minerals::Fe] = quantity;
            return *this;
        }

        Substract &withN(quantity_t quantity)
        {
            (*this)[nutrients::Minerals::N] = quantity;
            return *this;
        }

        template <class Nutrient_t>
        void addNutrient(Nutrient_t type, quantity_t quantity) //TODO: think about quantities vs concentration
        {
            if (type != Nutrient_t::COUNT)
                (*this)[type] += quantity;
        }

        template <class Nutrient_t>
        quantity_t takeNutrient(Nutrient_t type, quantity_t quantity)
        {
            checkNutrientIndex(type);

            if ((*this)[type] > quantity)
            {
                (*this)[type] -= quantity;
            }
            else
            {
                quantity = (*this)[type];
                (*this)[type] = 0;
            }
            return quantity;
        }

        template <class Nutrient_t>
        const quantity_t &getNutrient(Nutrient_t type) const
        {
            return (*this)[type];
        }

    private:
        quantity_t &operator[](nutrients::Minerals typeIdx)
        {
            int idx = static_cast<int>(typeIdx);
            return m_minerals[idx];
        }
        const quantity_t &operator[](nutrients::Minerals typeIdx) const
        {
            int idx = static_cast<int>(typeIdx);
            return m_minerals[idx];
        }
        quantity_t &operator[](nutrients::Vitamins typeIdx)
        {
            int idx = static_cast<int>(typeIdx);
            return m_vitamins[idx];
        }
        const quantity_t &operator[](nutrients::Vitamins typeIdx) const
        {
            int idx = static_cast<int>(typeIdx);
            return m_vitamins[idx];
        }

        template <class Nutrient_t>
        static void checkNutrientIndex(Nutrient_t type) noexcept
        {
            if (type >= Nutrient_t::COUNT)
                std::cerr << "\nERROR: trying to get invalid nutrient Index.\n";
        }

        std::vector<quantity_t> m_minerals;
        std::vector<quantity_t> m_vitamins;
    };
} // namespace core
