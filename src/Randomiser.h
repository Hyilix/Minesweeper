#ifndef RANDOMISER_H
#define RANDOMISER_H

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Utils.hpp"

#define DEFAULT_GRACE_SCALE 3

#define MAX_ATTEMPTS 10

#define DEBUG_RANDOM_POSITION_PRINT false

// Generate random 2d positions on a grid
class Randomiser_2D {
    public:
        Randomiser_2D(pair_uint dimensions);
        ~Randomiser_2D();

        /* vvv Preparation functions vvv */
        void set_random_count(unsigned int count);
        void set_init_position(pair_uint position);
        void set_init_position(unsigned int x_pos, unsigned int y_pos);
        void set_grace_scale(unsigned int scale);
        /* ^^^ Preparation functions ^^^ */

        /* vvv Utils functions vvv */
        /*
         * Create a preoccupied zone in the grid of a square shape
         * of size *grace_scale* with top-left corner *init_position*
         */
        void apply_grace_to_grid();
        void randomise();
        vec_2d_bool get_grid();
        std::vector<pair_uint> get_bomb_coordinates();
        std::vector<pair_uint> get_grace_coordinates();
        /* ^^^ Utils functions ^^^ */

        /* vvv Debug functions vvv */
        void DEBUG_print_grid();
        void DEBUG_print_bombs();
        /* ^^^ Debug functions ^^^ */

    private:
        vec_2d_bool grid;
        std::vector<pair_uint> bomb_coordinates;
        std::vector<pair_uint> grace_coordinates;

        pair_uint map_dimensions;
        unsigned int no_rand;

        pair_uint init_position;
        unsigned int grace_scale = DEFAULT_GRACE_SCALE;

        void create_empty_grid();
        /*
         * Attempt to fill a random position in the grid with true.
         * Will return *true* if succesful, or *false* on too many failed attempts
         */
        bool fill_random_pos();
};

#endif

