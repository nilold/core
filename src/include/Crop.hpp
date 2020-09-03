#pragma once

#include <Substract.hpp>
#include <Inffectable.hpp>

namespace core
{
    using health_t = std::int_fast8_t;

    class Crop : public Substract, public Inffectable
    {
    public:
        Crop(
            std::string specie,
            health_t health = 100,
            health_t maxHealth = 100,
            health_t healthDevelopThreshold = 50,
            std::int_fast8_t cyclesPerStage = 10);

        Crop(const Crop &c) = delete;
        Crop(Crop &&c);
        ~Crop() = default;

        void cycle();
        Crop &needs(nutrients::Minerals type, nutrients::quantity_t quantity);

        // Getters and setters
        health_t health() const;
        std::int_fast8_t phenologicalStage() const;
        std::string specie() const;
        void setSpecie(const std::string &specie);

    private:
        void develop();
        void cycleAgents();
        void updateHealth();

    private:
        std::string m_specie{};
        health_t m_health{};
        health_t m_maxHealth{};
        health_t m_healthDevelopThreshold{};
        std::int_fast8_t m_cyclesPerStage{};
        std::int_fast8_t m_stageCycles{0};
        std::int_fast8_t m_stage{0};
        std::unordered_map<nutrients::Minerals, nutrients::quantity_t> m_needs;
    };
} // namespace core
