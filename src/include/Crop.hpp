#pragma once

#include <Organism.hpp>

namespace core
{
    class Crop : public Organism
    {
    public:
        Crop(std::string specie) : Organism(), m_specie{specie} {}
        Crop(const Crop &c) = delete;
        Crop(Crop &&c) : Organism(std::move(c)), m_specie(c.m_specie) {} // TODO: is this right?
        ~Crop() = default;

        std::string getSpecie() { return m_specie; }

        void setSpecie(const std::string &specie) { m_specie = specie; }

    private:
        std::string m_specie{};
    };
} // namespace core

namespace core
{

} // namespace core
