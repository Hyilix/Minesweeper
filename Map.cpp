#include "Map.hpp"

Map::Map() {
    std::cout << "Map initialised!" << std::endl;
}

Map::~Map() {
    std::cout << "Map destroyed!" << std::endl;
}

void Map::create_empty_map() {
    Map::map = new Tile**[Map::dimensions.first];

    for (int i = 0; i < Map::dimensions.first; i++) {
        Map::map[i] = new Tile*[Map::dimensions.second];
    }
}

void Map::create_empty_map(std::pair<unsigned int, unsigned int> dimensions) {
    Map::map = new Tile**[dimensions.first];

    for (int i = 0; i < dimensions.first; i++) {
        Map::map[i] = new Tile*[dimensions.second];
    }

    Map::set_dimensions(dimensions);
}

void Map::create_empty_map(unsigned int width, unsigned int height) {
    Map::map = new Tile**[width];

    for (int i = 0; i < width; i++) {
        Map::map[i] = new Tile*[height];
    }

    Map::set_dimensions(width, height);
}

void Map::set_dimensions(std::pair<unsigned int, unsigned int> dimensions) {
    Map::dimensions = dimensions;
}

void Map::set_dimensions(unsigned int width, unsigned int height) {
    Map::dimensions.first = width;
    Map::dimensions.second = height;
}

void Map::set_bomb_count(unsigned int count) {
    Map::bombs = count;
}

void Map::set_flag_count(unsigned int count) {
    Map::flags = count;
}

std::pair<unsigned int, unsigned int> Map::get_dimensions() {
    return Map::dimensions;
}

unsigned int Map::get_bomb_count() {
    return Map::bombs;
}

unsigned int Map::get_flag_count() {
    return Map::flags;
}

Tile ***Map::get_map() {
    return Map::map;
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

