#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include <iostream>

#include "Map.hpp"

class GameHandler {
    public:
        GameHandler();
        ~GameHandler();

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

        void create_map();
        Map *get_map();

        void set_fps(unsigned int FPS);
        unsigned int get_fps();

        void calculate_frame_delay(); 
        unsigned int get_frame_delay();

    private:
        bool running = 0;
        SDL_Window *window;
        SDL_Renderer *renderer;

        Map *map;

        // background color
        SDL_Color color;

        unsigned int FPS;
        unsigned int frame_delay;
};

#endif
