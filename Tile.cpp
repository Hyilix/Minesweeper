#include "Tile.hpp"

Tile::Tile() {
    std::cout << "Tile initialised!" << std::endl;

    // set default colors
    this->set_hidden_color(180, 180, 180, 0);
    this->set_exposed_color(128, 128, 128, 0);
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

void Tile::set_exposed(bool value) {
    this->has_exposed = value;
}

bool Tile::is_exposed() {
    return this->has_exposed;
}

void Tile::set_hidden_color(SDL_Color color) {
    this->hidden_color = color;
}

void Tile::set_hidden_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    this->hidden_color.r = r;
    this->hidden_color.g = g;
    this->hidden_color.b = b;
    this->hidden_color.a = a;
}

void Tile::set_exposed_color(SDL_Color color) {
    this->exposed_color = color;
}

void Tile::set_exposed_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    this->exposed_color.r = r;
    this->exposed_color.g = g;
    this->exposed_color.b = b;
    this->exposed_color.a = a;
}

SDL_Color Tile::get_hidden_color() {
    return this->hidden_color;
}

SDL_Color Tile::get_exposed_color() {
    return this->exposed_color;
}

void Tile::switch_to_bomb_color() {
    this->set_exposed_color(255, 0, 0, 0);
}

void Tile::switch_to_flag_color() {
    this->set_hidden_color(0, 255, 0, 0);
}

void Tile::switch_to_normal_color() {
    this->set_hidden_color(255, 255, 255, 0);
}

void Tile::create_tile_rectangle() {
    this->tile_rect = {(int)this->position.first,
                        (int)this->position.second,
                        (int)this->size.first,
                        (int)this->size.second};
}

SDL_Rect Tile::get_tile_rectangle() {
    return this->tile_rect;
}

void Tile::draw_tile(SDL_Renderer *renderer) {
    SDL_Color actual_color = this->get_exposed_color();

    // determine the color
    if (this->is_exposed() == false) {
        actual_color = this->get_hidden_color();
    }

    // draw the rectangle
    SDL_SetRenderDrawColor(renderer, actual_color.r,
                                    actual_color.g,
                                    actual_color.b,
                                    actual_color.a);

    SDL_RenderFillRect(renderer, &this->tile_rect);
    SDL_RenderDrawRect(renderer, &this->tile_rect);
}

