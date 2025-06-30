#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

class GameHandler {
    public:
        GameHandler();
        ~GameHandler();

        void init(Uint32 flags = SDL_INIT_EVERYTHING);
        void create_window(std::string name, int x, int y, int h, int w, Uint32 flags);
        void create_renderer(SDL_Window *window, int index, Uint32 flags);

        void event_handler();

        bool is_running();
        SDL_Window *get_window();
        SDL_Renderer *get_renderer();

        void set_running(bool value);

    private:
        bool running = 0;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif
