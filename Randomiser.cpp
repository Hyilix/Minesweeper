#include "Randomiser.h"
#include "Custom_Types.h"

Randomiser_2D::Randomiser_2D(pair_uint dimensions) {
    srand(time(NULL));

    this->map_dimensions = dimensions;
    this->create_empty_grid();

    pair_uint default_position(0, 0);
    this->init_position = default_position;
    this->set_random_count(1);
}

Randomiser_2D::~Randomiser_2D() {
}

void Randomiser_2D::set_random_count(unsigned int count) {
    this->no_rand = count;
}

void Randomiser_2D::set_init_position(pair_uint position) {
    this->init_position = position;
}

void Randomiser_2D::set_init_position(unsigned int x_pos, unsigned int y_pos) {
    pair_uint position(x_pos, y_pos);
    this->init_position = position;
}

void Randomiser_2D::set_grace_scale(unsigned int scale) {
    this->grace_scale = scale;
}

void Randomiser_2D::randomise() {
    for (unsigned int i = 0; i < this->no_rand; i++) {
        this->fill_random_pos();
    }
}

vec_2d_bool Randomiser_2D::get_grid() {
    return this->grid;
}

std::vector<pair_uint> Randomiser_2D::get_bomb_coordinates() {
    return this->bomb_coordinates;
}

std::vector<pair_uint> Randomiser_2D::get_grace_coordinates() {
    return this->grace_coordinates;
}

void Randomiser_2D::create_empty_grid() {
    unsigned int rows = this->map_dimensions.second;
    unsigned int cols = this->map_dimensions.first;

    vec_2d_bool grid(rows, std::vector<bool>(cols, false));
    this->grid = grid;
}

void Randomiser_2D::apply_grace_to_grid() {
    int x_pos = this->init_position.first;
    int y_pos = this->init_position.second;
    int scale = this->grace_scale;

    // Apply a square onto the grid
    // The square is centered in x_pos, y_pos
    for (int y = y_pos - scale / 2; y <= y_pos + scale / 2; y++) {
        // Out-of-bounds check
        if (y < 0 || y >= this->map_dimensions.second) {
            std::cout << "ERROR y: " << y << std::endl;
            continue;
        }
        for (int x = x_pos - scale / 2; x <= x_pos + scale / 2; x++) {
            // Out-of-bounds check
            if (x < 0 || x >= this->map_dimensions.first) {
                std::cout << "ERROR x: " << x << std::endl;
                continue;
            }
            // std::cout << "GRACE: " << y << " " << x << std::endl;
            this->grid[y][x] = true;

            pair_uint temp_coords(x, y);
            this->grace_coordinates.emplace_back(temp_coords);
        }
    }
}

bool Randomiser_2D::fill_random_pos() {
    unsigned int x_size = this->grid[0].size();
    unsigned int y_size = this->grid.size();

    bool attempt_random_generation = true;
    unsigned int attempts = 0;

    while (attempt_random_generation == true) {
        unsigned int x_rand_pos = rand() % x_size;
        unsigned int y_rand_pos = rand() % y_size;

        if (DEBUG_RANDOM_POSITION_PRINT) {
            std::cout << "THIS ATTEMPT: " << this->grid[y_rand_pos][x_rand_pos] << " ";
            std::cout << "POSITION: " << x_rand_pos << " " << y_rand_pos << " ";
            std::cout << "ATTEMPTS: " << attempts << std::endl;
        }

        if (this->grid[y_rand_pos][x_rand_pos] == false) {
            this->grid[y_rand_pos][x_rand_pos] = true;

            pair_uint temp_coords(x_rand_pos, y_rand_pos);
            this->bomb_coordinates.emplace_back(temp_coords);

            attempt_random_generation = false;
        }
        attempts++;
        // Too many failed attempts, stop
        if (attempts >= MAX_ATTEMPTS) {
            return false;
        }
    }
    return true;
}

void Randomiser_2D::DEBUG_print_grid() {
    auto grid = this->grid;

    for (unsigned int y = 0; y < grid.size(); y++) {
        for (unsigned int x = 0; x < grid[y].size(); x++) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void Randomiser_2D::DEBUG_print_bombs() {
    auto bombs = this->bomb_coordinates;

    for (unsigned int i = 0; i < bombs.size(); i++) {
        std::cout << bombs[i].first << " " << bombs[i].second << std::endl;
    }
}

