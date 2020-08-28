#pragma once

namespace core
{
    struct pos { unsigned x, y; };
    class Tile
    {
        public:
        Tile(unsigned x, unsigned y): m_pos{x, y}{}
        ~Tile() = default;
        Tile(const Tile&) = delete;
        Tile(const Tile&&) = delete;

        private:
        struct pos m_pos{0, 0};
    };
}