#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include <iostream>

#include "Map.hpp"

typedef struct {
    // map number of tiles
    unsigned int map_x_size;
    unsigned int map_y_size;

    unsigned int bomb_count;
} game_settings_t;

class GameHandler {
    public:
        GameHandler();
        ~GameHandler();

        bool game_started = false;

        void init(Uint32 flags = SDL_INIT_EVERYTHING);
        void create_window(char *name, int x, int y, int h, int w, Uint32 flags);
        void create_renderer(SDL_Window *window, int index, Uint32 flags);

        void set_background_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void set_background_color(SDL_Color color);

        SDL_Color get_background_color();

        void event_handler();
        void render_logic();

        bool is_running();
        SDL_Window *get_window();
        SDL_Renderer *get_renderer();

        void set_running(bool value);

        void create_map(game_settings_t *settings);
        void create_map_debug();
        Map *get_map();

        void set_fps(unsigned int FPS);
        unsigned int get_fps();

        void apply_fps_limit();

    private:
        void calculate_frame_delay(); 

        bool running = false;
        SDL_Window *window;
        SDL_Renderer *renderer;

        Map *map;

        // background color
        SDL_Color color;

        unsigned int FPS;
        unsigned int frame_delay;
};

#endif

