#include "Tile.hpp"
#include <SDL2/SDL_render.h>

Tile::Tile() {
}

Tile::~Tile() {
    SDL_DestroyTexture(this->text_texture);
    SDL_FreeSurface(this->text);
}

bool Tile::set_exposed_tile(bool force_reveal) {
    bool is_exposed = this->is_exposed();
    bool is_flagged = this->is_flagged();

    if ((is_exposed == false && is_flagged == false) || force_reveal == true) {
        this->set_exposed(true);
        return true;
    }
    return false;
}

void Tile::set_flag_tile() {
    bool is_exposed = this->is_exposed();
    bool is_flagged = this->is_flagged();

    if (is_exposed == false) {
        this->set_flag(!is_flagged);
    }
}

void Tile::set_tile_number(int number) {
    this->tile_number = number;
}

void Tile::increment_tile_number(int number) {
    this->tile_number += number;
}

int Tile::get_tile_number() {
    return this->tile_number;
}

bool Tile::click_action(Uint8 button, unsigned int *revealed_tiles) {
    if (button == LEFT_CLICK) {
        bool success = this->set_exposed_tile();
        if (this->is_bomb() && success) {
            std::cout << "BOOOM!";
            return true;
        }
        if (revealed_tiles && success) {
            *revealed_tiles += 1;
        }
    }
    else if (button == RIGHT_CLICK) {
        this->set_flag_tile();
    }
    return false;
}

std::pair<unsigned int, unsigned int> Tile::get_position() {
    return this->position;
}

std::pair<unsigned int, unsigned int> Tile::get_raw_position() {
    unsigned int raw_x = this->position.first / this->size.first;
    unsigned int raw_y = this->position.second / this->size.second;
    std::pair<unsigned int, unsigned int> raw_pos(raw_x, raw_y);

    return raw_pos;
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

    if (value == true) {
        this->switch_to_flag_color();
    }
    else {
        this->switch_to_normal_color();
    }
}

bool Tile::is_flagged() {
    return this->has_flag;
}

void Tile::set_bomb(bool value) {
    this->has_bomb = value;

    if (value == true) {
        this->switch_to_bomb_color();
        this->tile_number = 9;
    }
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

// TODO: These can be simplified to one function each, using an enum or something.
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
    this->set_hidden_color(180, 180, 180, 0);
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

void Tile::draw_tile(SDL_Renderer *renderer, TTF_Font *font, bool force_draw_bomb) {
    // Determine the color of the tile
    SDL_Color actual_color = this->get_exposed_color();

    if (this->is_exposed() == false) {
        if (this->is_bomb() && force_draw_bomb && !this->is_flagged()) {
            this->switch_to_bomb_color();
            actual_color = this->get_exposed_color();
        }
        else {
            actual_color = this->get_hidden_color();
        }
    }

    // draw the rectangle
    SDL_SetRenderDrawColor(renderer, actual_color.r,
                                    actual_color.g,
                                    actual_color.b,
                                    actual_color.a);

    SDL_RenderFillRect(renderer, &this->tile_rect);
    SDL_RenderDrawRect(renderer, &this->tile_rect);

    // Draw tile text
    if (this->is_exposed() == true) {
        if (this->tile_number > 0 && !this->is_bomb() && !this->is_flagged()) {
            SDL_RenderCopy(renderer, this->text_texture, NULL, &(this->dest));
        }
    }
}

void Tile::prep_text_rendering(SDL_Renderer *renderer, SDL_Color color, TTF_Font *font) {
    this->set_text(color, font);
    this->set_text_texture(renderer);
    this->set_text_dest();
}

void Tile::set_text(SDL_Color color, TTF_Font *font) {
    std::string num = std::to_string(this->tile_number);

    this->text = TTF_RenderText_Solid(font, num.c_str(), color);
}

void Tile::set_text_texture(SDL_Renderer *renderer) {
    this->text_texture = SDL_CreateTextureFromSurface(renderer, text);
}

void Tile::set_text_dest() {
    pair_uint temp_pos = this->get_position();

    this->dest = {
        (int)temp_pos.first + (int)this->size.first / 4,
        (int)temp_pos.second + (int)this->size.second / 4,
        this->text->w,
        this->text->h
    };
}

