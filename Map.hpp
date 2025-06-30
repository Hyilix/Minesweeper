#ifndef MAP_HPP
#define MAP_HPP

#include "Tile.hpp"

class Map {
    public:
        Map();
        ~Map();

        void create_empty_map();
        void create_empty_map(std::pair<unsigned int, unsigned int> dimensions);
        void create_empty_map(unsigned int width, unsigned int height);

        void set_dimensions(std::pair<unsigned int, unsigned int> dimensions);
        void set_dimensions(unsigned int width, unsigned int height);
        void set_bomb_count(unsigned int count);
        void set_flag_count(unsigned int count);

        std::pair<unsigned int, unsigned int> get_dimensions();
        unsigned int get_bomb_count();
        unsigned int get_flag_count();
        Tile **get_map();

        Tile *get_tile_from_position(std::pair<unsigned int, unsigned int> position);
        Tile *get_tile_from_position(unsigned int x, unsigned int y);

        Tile ***get_tile_neighbors(std::pair<unsigned int, unsigned int> position);
        Tile ***get_tile_neighbors(unsigned int x, unsigned int y);
        Tile ***get_tile_neighbors(Tile *tile);

    private:
        std::pair<unsigned int, unsigned int> dimensions;
        unsigned int bombs;
        unsigned int flags;

        Tile **map;
};

#endif
