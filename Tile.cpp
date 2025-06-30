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
    return this->position;
}

std::pair<unsigned int, unsigned int> Tile::get_size() {
    return this->size;
}

void Tile::set_position(std::pair<unsigned int, unsigned int> position) {
    this->position = position;
}

void Tile::set_position(unsigned int x, unsigned int y) {
    this->position.first = x;
    this->position.second = y;
}

void Tile::set_size(std::pair<unsigned int, unsigned int> size) {
    this->size = size;
}

void Tile::set_size(unsigned int width, unsigned int height) {
    this->size.first = width;
    this->size.second = height;
}

void Tile::set_flag(bool value) {
    this->has_flag = value;
}

bool Tile::is_flagged() {
    return this->has_flag;
}

void Tile::set_bomb(bool value) {
    this->has_bomb = value;
}

bool Tile::is_bomb() {
    return this->has_bomb;
}

