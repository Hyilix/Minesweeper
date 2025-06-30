#ifndef TILE_HPP
#define TILE_HPP

#include <cstdint>
#include <utility>

class Tile {
    public:
        Tile();
        ~Tile();

        void click_action();
        Tile *get_neighbors();

    private:
        std::pair<unsigned int, unsigned int> position;
        std::pair<unsigned int, unsigned int> size;

        uint8_t number = 0;
};

#endif
