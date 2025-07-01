#include "Map.hpp"

Map::Map() {
    std::cout << "Map initialised!" << std::endl;

    this->set_universal_tile_size(50, 50);
}

Map::~Map() {
    std::cout << "Map destroyed!" << std::endl;
}

void Map::create_empty_map() {
    this->tiles = new Tile**[this->dimensions.second];

    for (int i = 0; i < this->dimensions.second; i++) {
        this->tiles[i] = new Tile*[this->dimensions.first];
    }
}

void Map::create_empty_map(std::pair<unsigned int, unsigned int> dimensions) {
    this->tiles = new Tile**[dimensions.second];

    for (int i = 0; i < dimensions.second; i++) {
        this->tiles[i] = new Tile*[dimensions.first];
    }

    this->set_dimensions(dimensions);
}

void Map::create_empty_map(unsigned int width, unsigned int height) {
    this->tiles = new Tile**[height];

    for (int i = 0; i < height; i++) {
        this->tiles[i] = new Tile*[width];
    }

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

            this->get_map()[y][x] = temp_tile;
            temp_tile->draw_tile(renderer);
        }
    }
}

void Map::render_map(SDL_Renderer *renderer) {
    unsigned int x_pos = this->get_dimensions().first;
    unsigned int y_pos = this->get_dimensions().second;

    unsigned int x_size = this->get_universal_tile_size().first;
    unsigned int y_size = this->get_universal_tile_size().second;

    for (unsigned int y = 0; y < y_pos; y++) {
        for (unsigned int x = 0; x < x_pos; x++) {
            (this->get_map()[y][x])->draw_tile(renderer);
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

Tile ***Map::get_map() {
    return this->tiles;
}

Tile *Map::get_tile_from_position(std::pair<unsigned int, unsigned int> position) {
    // TODO
}

Tile *Map::get_tile_from_position(unsigned int x, unsigned int y) {
    // TODO
}

Tile ***Map::get_tile_neighbors(std::pair<unsigned int, unsigned int> position) {
    // TODO
}

Tile ***Map::get_tile_neighbors(unsigned int x, unsigned int y) {
    // TODO
}

Tile ***Map::get_tile_neighbors(Tile *tile) {
    // TODO
}

