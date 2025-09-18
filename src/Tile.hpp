#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <cstdint>
#include <utility>

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Utils.hpp"

#define TILE_DEFAULT_SIZE 50

class Tile {
    public:
        Tile();
        ~Tile();

        // Basic tile actions
        bool set_exposed_tile(bool force_reveal = false);
        void set_flag_tile();

        void set_tile_number(int number);
        void increment_tile_number(int number = 1);
        int get_tile_number();

        bool click_action(Uint8 button, unsigned int *revealed_tiles = NULL);

        std::pair<unsigned int, unsigned int> get_position();
        std::pair<unsigned int, unsigned int> get_raw_position();
        std::pair<unsigned int, unsigned int> get_size();

        void set_position(std::pair<unsigned int, unsigned int> position);
        void set_position(unsigned int x, unsigned int y);

        void set_size(std::pair<unsigned int, unsigned int> size);
        void set_size(unsigned int width, unsigned int height);

        void set_flag(bool value);
        bool is_flagged();

        void set_bomb(bool value);
        bool is_bomb();

        void set_exposed(bool value);
        bool is_exposed();

        void set_hidden_color(SDL_Color color);
        void set_hidden_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void set_exposed_color(SDL_Color color);
        void set_exposed_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        SDL_Color get_hidden_color();
        SDL_Color get_exposed_color();

        void switch_to_bomb_color();
        void switch_to_flag_color();
        void switch_to_normal_color();

        void create_tile_rectangle();
        SDL_Rect get_tile_rectangle();

        void draw_tile(SDL_Renderer *renderer, TTF_Font *font = NULL);

        void prep_text_rendering(SDL_Renderer *renderer, SDL_Color color, TTF_Font *font);

    private:
        void set_text(SDL_Color color, TTF_Font *font);
        void set_text_texture(SDL_Renderer *renderer);
        void set_text_dest();

        std::pair<unsigned int, unsigned int> position;
        std::pair<unsigned int, unsigned int> size;

        // the number of bombs near this tile. 
        int tile_number = 0;
        bool has_exposed = false;

        bool has_flag = false;
        bool has_bomb = false;

        SDL_Color hidden_color = {180, 180, 180, 0};
        SDL_Color exposed_color = {128, 128, 128, 0};

        SDL_Rect tile_rect;

        SDL_Surface *text;
        SDL_Texture *text_texture;
        SDL_Rect dest;
};

#endif

