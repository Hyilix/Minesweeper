#include "Map.hpp"
#include "Custom_Types.h"
#include "Randomiser.h"

Map::Map() {
    std::cout << "Map initialised!" << std::endl;

    unsigned int default_x_size = 5;
    unsigned int default_y_size = 10;

    this->set_universal_tile_size(50, 50);
    this->set_dimensions(default_x_size, default_y_size);

    pair_uint temp_pair(default_x_size, default_y_size);
    this->randomiser = new Randomiser_2D(temp_pair);
}

Map::Map(unsigned int x_size, unsigned int y_size) {
    std::cout << "Map initialised with dimensions: " << std::endl;
    std::cout << x_size << " " << y_size << std::endl;

    this->set_universal_tile_size(50, 50);
    this->set_dimensions(x_size, y_size);

    pair_uint temp_pair(x_size, y_size);
    this->randomiser = new Randomiser_2D(temp_pair);
}

Map::~Map() {
    std::cout << "Map destroyed!" << std::endl;
}

void Map::create_empty_map() {
    // Create an empty map of Tile objects
    this->tiles = new Tile**[this->dimensions.second];

    for (int i = 0; i < this->dimensions.second; i++) {
        this->tiles[i] = new Tile*[this->dimensions.first];
    }
}

void Map::create_empty_map(std::pair<unsigned int, unsigned int> dimensions) {
    // Create an empty map of Tile objects with specified dimensions
    this->tiles = new Tile**[dimensions.second];

    for (int i = 0; i < dimensions.second; i++) {
        this->tiles[i] = new Tile*[dimensions.first];
    }

    // Save the current dimensions
    this->set_dimensions(dimensions);
}

void Map::create_empty_map(unsigned int width, unsigned int height) {
    // Create an empty map of Tile objects with specified dimensions
    this->tiles = new Tile**[height];

    for (int i = 0; i < height; i++) {
        this->tiles[i] = new Tile*[width];
    }

    // Save the current dimensions
    this->set_dimensions(width, height);
}

void Map::set_dimensions(std::pair<unsigned int, unsigned int> dimensions) {
    this->dimensions = dimensions;
}

void Map::set_dimensions(unsigned int width, unsigned int height) {
    this->dimensions.first = width;
    this->dimensions.second = height;
}

void Map::set_bomb_count(unsigned int count) {
    this->bombs = count;
}

void Map::set_flag_count(unsigned int count) {
    this->flags = count;
}

void Map::set_universal_tile_size(std::pair<unsigned int, unsigned int> size) {
    this->universal_tile_size = size;
}

void Map::set_universal_tile_size(unsigned int width, unsigned int height) {
    this->universal_tile_size.first = width;
    this->universal_tile_size.second = height;
}

std::pair<unsigned int, unsigned int> Map::get_universal_tile_size() {
    return this->universal_tile_size;
}

void Map::fill_map(SDL_Renderer *renderer) {
    unsigned int x_pos = this->get_dimensions().first;
    unsigned int y_pos = this->get_dimensions().second;

    unsigned int x_size = this->get_universal_tile_size().first;
    unsigned int y_size = this->get_universal_tile_size().second;

    for (unsigned int y = 0; y < y_pos; y++) {
        for (unsigned int x = 0; x < x_pos; x++) {
            Tile *temp_tile = new Tile;

            temp_tile->set_size(x_size, y_size);
            temp_tile->set_position(x * x_size, y * y_size);

            temp_tile->create_tile_rectangle();

            this->get_tiles()[y][x] = temp_tile;
            temp_tile->draw_tile(renderer);
        }
    }
}

void Map::render_map(SDL_Renderer *renderer) {
    unsigned int x_pos = this->get_dimensions().first;
    unsigned int y_pos = this->get_dimensions().second;

    // unsigned int x_size = this->get_universal_tile_size().first;
    // unsigned int y_size = this->get_universal_tile_size().second;

    for (unsigned int y = 0; y < y_pos; y++) {
        for (unsigned int x = 0; x < x_pos; x++) {
            (this->get_tiles()[y][x])->draw_tile(renderer);
        }
    }
}

std::pair<unsigned int, unsigned int> Map::get_dimensions() {
    return this->dimensions;
}

unsigned int Map::get_bomb_count() {
    return this->bombs;
}

unsigned int Map::get_flag_count() {
    return this->flags;
}

Tile ***Map::get_tiles() {
    return this->tiles;
}

std::pair<unsigned int, unsigned int> Map::get_sanitized_position(std::pair<unsigned int, unsigned int> position) {
    unsigned int tile_x_size = this->get_universal_tile_size().first;
    unsigned int tile_y_size = this->get_universal_tile_size().second;

    std::pair<unsigned int, unsigned int> sanitized;

    sanitized.first = position.first / tile_x_size;
    sanitized.second = position.second / tile_y_size;

    return sanitized;
}

std::pair<unsigned int, unsigned int> Map::get_sanitized_position(unsigned int x, unsigned int y) {
    unsigned int tile_x_size = this->get_universal_tile_size().first;
    unsigned int tile_y_size = this->get_universal_tile_size().second;

    std::pair<unsigned int, unsigned int> sanitized;

    sanitized.first = x / tile_x_size;
    sanitized.second = y / tile_y_size;

    return sanitized;
}

Tile *Map::get_tile_from_position(std::pair<unsigned int, unsigned int> position) {
    std::pair<unsigned int, unsigned int> sanitized = this->get_sanitized_position(position);

    unsigned int y_sanitized = sanitized.second;
    unsigned int x_sanitized = sanitized.first;

    return this->get_tiles()[y_sanitized][x_sanitized];
}

Tile *Map::get_tile_from_position(unsigned int x, unsigned int y) {
    std::pair<unsigned int, unsigned int> sanitized = this->get_sanitized_position(x, y);

    unsigned int y_sanitized = sanitized.second;
    unsigned int x_sanitized = sanitized.first;

    return this->get_tiles()[y_sanitized][x_sanitized];
}

Tile ***__make_empty_neighbor_map() {
    Tile ***neighbors = new Tile**[3];

    for (unsigned int i = 0; i < 3; i++) {
        neighbors[i] = new Tile*[3];
    }
    return neighbors;
}

Tile ***Map::get_tile_neighbors(std::pair<unsigned int, unsigned int> position) {
    Tile ***neighbors = __make_empty_neighbor_map();

    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 3; x++) {
            neighbors[y][x] = this->tiles[position.second + y - 1][position.first + x - 1];
        }
    }
    return neighbors;
}

Tile ***Map::get_tile_neighbors(unsigned int x_pos, unsigned int y_pos) {
    Tile ***neighbors = __make_empty_neighbor_map();

    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 3; x++) {
            neighbors[y][x] = this->tiles[y_pos + y - 1][x_pos + x - 1];
        }
    }
    return neighbors;
}

Tile ***Map::get_tile_neighbors(Tile *tile) {
    auto position = tile->get_raw_position();
    Tile ***neighbors = __make_empty_neighbor_map();

    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 3; x++) {
            int temp_pos_x = int(position.second) + int(y) - 1;
            int temp_pos_y = int(position.first) + int(x) - 1;

            std::cout << "NEIGHBOR POSITION: " << temp_pos_x << " " << temp_pos_y << std::endl;

            // Out of bounds check
            if (temp_pos_x < 0 || temp_pos_x >= this->dimensions.first ||
                temp_pos_y < 0 || temp_pos_y >= this->dimensions.second) {
                // std::cout << "OUT OF BOUNDS" << std::endl;
                continue;
            }

            neighbors[y][x] = this->tiles[temp_pos_y][temp_pos_x];
            // std::cout << "PREV :" << this->tiles[temp_pos_y][temp_pos_x]->get_tile_number() << std::endl;
        }
    }
    return neighbors;
}

Randomiser_2D *Map::get_randomiser() {
    return this->randomiser;
}

void Map::set_bombs(std::vector<pair_uint> bombs) {
    auto bombs_size = bombs.size();

    for (unsigned int i = 0; i < bombs_size; i++) {
        auto current_bomb = bombs[i];
        this->tiles[current_bomb.second][current_bomb.first]->set_bomb(true);

        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                // Skip the tile itself
                if (x == 0 && y == 0) {
                    continue;
                }

                int temp_y_pos = int(current_bomb.second + y);
                int temp_x_pos = int(current_bomb.first + x);
                pair_uint temp_pos(temp_x_pos, temp_y_pos);

                // Out of bounds check
                if (temp_y_pos < 0 || temp_y_pos >= this->dimensions.second ||
                    temp_x_pos < 0 || temp_x_pos >= this->dimensions.first) {
                        continue;
                }

                if (std::find(bombs.begin(), bombs.end(), temp_pos) == bombs.end()) {
                    this->tiles[temp_y_pos][temp_x_pos]->increment_tile_number();
                }
            }
        }
        // this->tiles[current_bomb.second][current_bomb.first]->set_exposed_tile();
    }
}

void Map::open_tiles(std::vector<pair_uint> tiles) {
    auto tiles_size = tiles.size();

    for (unsigned int i = 0; i < tiles_size; i++) {
        auto current_tile = tiles[i];
        Tile *temp_tile = this->tiles[current_tile.second][current_tile.first];
        this->tile_action(temp_tile, LEFT_CLICK);
        // this->tiles[current_tile.second][current_tile.first]->click_action(LEFT_CLICK);
    }
}

void Map::tile_action(Tile *tile, uint8_t button) {
    tile->click_action(button);

    unsigned int y_pos = tile->get_raw_position().second;
    unsigned int x_pos = tile->get_raw_position().first;

    if (button == LEFT_CLICK && tile->get_tile_number() == 0) {
        for (unsigned int y = 0; y < 3; y++) {
            for (unsigned int x = 0; x < 3; x++) {
                int temp_y_pos = int(y_pos + y) - 1;
                int temp_x_pos = int(x_pos + x) - 1;

                // std::cout << "NEIGHBOR POSITION: " << temp_x_pos << " " << temp_y_pos << std::endl;
                // Out of bounds check
                if (temp_y_pos < 0 || temp_y_pos >= this->dimensions.second ||
                    temp_x_pos < 0 || temp_x_pos >= this->dimensions.first) {
                        // std::cout << "OUT OF BOUNDS" << std::endl;
                        continue;
                }

                Tile *temp_tile = this->tiles[temp_y_pos][temp_x_pos];

                // std::cout << "Tile Number: " << temp_tile->get_tile_number() << std::endl;
                if (!temp_tile->is_exposed() && !temp_tile->is_flagged()) {
                    this->tile_action(temp_tile, button);
                }
            }
        }
    }
}

void Map::DEBUG_print_tile_numbers() {
    unsigned int map_size_x = this->dimensions.first;
    unsigned int map_size_y = this->dimensions.second;

    for (unsigned int y = 0; y < map_size_y; y++) {
        for (unsigned int x = 0; x < map_size_x; x++) {
            std::cout << this->tiles[y][x]->get_tile_number() << " ";
        }
    std::cout << std::endl;
    }
}

