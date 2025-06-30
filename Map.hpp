#ifndef MAP_HPP
#define MAP_HPP

#include "Tile.hpp"

class Map {
    public:
        Map();
        ~Map();

    private:
        std::pair<unsigned int, unsigned int> dimensions;
        unsigned int bombs;

        Tile *map;
};

#endif
