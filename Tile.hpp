#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <cstdint>
#include <utility>

#include <SDL2/SDL.h>

#define TILE_DEFAULT_SIZE 50

class Tile {
    public:
        Tile();
        ~Tile();

        void click_action();

        std::pair<unsigned int, unsigned int> get_position();
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

        void draw_tile(SDL_Renderer *renderer);

    private:
        std::pair<unsigned int, unsigned int> position;
        std::pair<unsigned int, unsigned int> size;

        // the number of bombs near this tile. 
        uint8_t tile_number = 0;
        bool has_exposed = false;

        bool has_flag = false;
        bool has_bomb = false;

        SDL_Color hidden_color;
        SDL_Color exposed_color;

        SDL_Rect tile_rect;
};

#endif
