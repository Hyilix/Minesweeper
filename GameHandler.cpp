#include "GameHandler.hpp"
#include <SDL2/SDL_events.h>

GameHandler::GameHandler() {
    std::cout << "Game Handler initialised!" << std::endl;

    // init functions
}

GameHandler::~GameHandler() {
    std::cout << "Game Handler Destroyed!" << std::endl;

    // cleanup functions
    SDL_Quit();
}

void GameHandler::init(Uint32 flags) {
    SDL_Init(flags);
}

void GameHandler::create_window(char *name, int x, int y, int h, int w, Uint32 flags) {
    GameHandler::window = SDL_CreateWindow(name, x, y, h, w, flags);
}

void GameHandler::create_renderer(SDL_Window *window, int index, Uint32 flags) {
    GameHandler::renderer = SDL_CreateRenderer(window, index, flags);
}

void GameHandler::event_handler() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            GameHandler::set_running(false);
            break;

        case SDL_KEYDOWN:
            // std::cout << "Scancode is " << event.key.keysym.scancode << std::endl;
            switch (event.key.keysym.scancode) {

            // ESC key
            case 41:
                GameHandler::set_running(false);
                break;

            case SDL_SCANCODE_W:
                std::cout << "Key W pressed\n";
                break;
            }
            break;
        }
    }
}

void GameHandler::set_running(bool value) {
    GameHandler::running = value;
}

bool GameHandler::is_running() {
    return GameHandler::running;
}

SDL_Window *GameHandler::get_window() {
    return GameHandler::window;
}

SDL_Renderer *GameHandler::get_renderer() {
    return GameHandler::renderer;
}
