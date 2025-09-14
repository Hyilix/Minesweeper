#ifndef MAP_HPP
#define MAP_HPP

#include <algorithm>

#include "Custom_Types.h"
#include "Randomiser.h"
#include "Tile.hpp"

class Map {
    public:
        Map();
        Map(unsigned int x_size, unsigned int y_size);
        ~Map();

        void create_empty_map();
        void create_empty_map(std::pair<unsigned int, unsigned int> dimensions);
        void create_empty_map(unsigned int width, unsigned int height);

        void set_dimensions(std::pair<unsigned int, unsigned int> dimensions);
        void set_dimensions(unsigned int width, unsigned int height);
        void set_bomb_count(unsigned int count);
        void set_flag_count(unsigned int count);

        void set_universal_tile_size(std::pair<unsigned int, unsigned int> size);
        void set_universal_tile_size(unsigned int width, unsigned int height);
        std::pair<unsigned int, unsigned int> get_universal_tile_size();

        void fill_map(SDL_Renderer *renderer);
        void render_map(SDL_Renderer *renderer, TTF_Font *font);

        std::pair<unsigned int, unsigned int> get_dimensions();
        unsigned int get_bomb_count();
        unsigned int get_flag_count();
        Tile ***get_tiles();

        std::pair<unsigned int, unsigned int> get_sanitized_position(std::pair<unsigned int, unsigned int> pos);
        std::pair<unsigned int, unsigned int> get_sanitized_position(unsigned int x, unsigned int y);

        Tile *get_tile_from_position(std::pair<unsigned int, unsigned int> position);
        Tile *get_tile_from_position(unsigned int x, unsigned int y);

        Tile ***get_tile_neighbors(std::pair<unsigned int, unsigned int> position);
        Tile ***get_tile_neighbors(unsigned int x, unsigned int y);
        Tile ***get_tile_neighbors(Tile *tile);

        Randomiser_2D *get_randomiser();

        void set_bombs(std::vector<pair_uint> bombs);
        void open_tiles(std::vector<pair_uint> tiles);

        void tile_action(Tile *tile, uint8_t button);

        void prep_tile_text(SDL_Renderer *renderer, SDL_Color color, TTF_Font *font);

        void DEBUG_print_tile_numbers();

    private:
        Randomiser_2D *randomiser;

        void fill_matrix_with_neighbors(Tile ***matrix, pair_uint tile_position);
        unsigned int get_flags_around_tile(Tile ***neighbors);

        // dimesnions in tiles
        std::pair<unsigned int, unsigned int> dimensions;

        // dimensions of a tile
        std::pair<unsigned int, unsigned int> universal_tile_size;

        unsigned int bombs;
        unsigned int flags;

        Tile ***tiles;

        SDL_Color tile_normal_color = {180, 180, 180, 0};
        SDL_Color tile_exposed_color = {128, 128, 128, 0};
        SDL_Color tile_flag_color = {0, 200, 0, 0};
        SDL_Color tile_bomb_color = {200, 0, 0, 0};
};

#endif

