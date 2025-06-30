#include "Tile.hpp"

Tile::Tile() {
    std::cout << "Tile initialised!" << std::endl;
}

Tile::~Tile() {
    std::cout << "Tile Destroyed!" << std::endl;
}

void Tile::click_action() {
    // TODO
}

std::pair<unsigned int, unsigned int> Tile::get_position() {
    return Tile::position;
}

std::pair<unsigned int, unsigned int> Tile::get_size() {
    return Tile::size;
}

void Tile::set_position(std::pair<unsigned int, unsigned int> position) {
    Tile::position = position;
}

void Tile::set_position(unsigned int x, unsigned int y) {
    Tile::position.first = x;
    Tile::position.second = y;
}

void Tile::set_size(std::pair<unsigned int, unsigned int> size) {
    Tile::size = size;
}

void Tile::set_size(unsigned int width, unsigned int height) {
    Tile::size.first = width;
    Tile::size.second = height;
}

void Tile::set_flag(bool value) {
    Tile::has_flag = value;
}

bool Tile::is_flagged() {
    return Tile::has_flag;
}

