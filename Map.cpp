#include "Map.hpp"

Map::Map() {
    std::cout << "Map initialised!" << std::endl;
}

Map::~Map() {
    std::cout << "Map destroyed!" << std::endl;
}

void Map::create_empty_map() {
    this->map = new Tile**[this->dimensions.first];

    for (int i = 0; i < this->dimensions.first; i++) {
        this->map[i] = new Tile*[this->dimensions.second];
    }
}

void Map::create_empty_map(std::pair<unsigned int, unsigned int> dimensions) {
    this->map = new Tile**[dimensions.first];

    for (int i = 0; i < dimensions.first; i++) {
        this->map[i] = new Tile*[dimensions.second];
    }

    this->set_dimensions(dimensions);
}

void Map::create_empty_map(unsigned int width, unsigned int height) {
    this->map = new Tile**[width];

    for (int i = 0; i < width; i++) {
        this->map[i] = new Tile*[height];
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
    return this->map;
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

