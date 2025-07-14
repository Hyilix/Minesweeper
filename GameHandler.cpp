#include "GameHandler.hpp"

GameHandler::GameHandler() {
    std::cout << "Game Handler initialised!" << std::endl;

    // vvv Init functions vvv
    this->set_fps(255);
    this->calculate_frame_delay();
}

GameHandler::~GameHandler() {
    std::cout << "Game Handler Destroyed!" << std::endl;

    // vvv Cleanup functions vvv
    SDL_Quit();
}

void GameHandler::init(Uint32 flags) {
    SDL_Init(flags);
    this->set_background_color(0, 0, 0, 0);
}

void GameHandler::create_window(char *name, int x, int y, int h, int w, Uint32 flags) {
    this->window = SDL_CreateWindow(name, x, y, h, w, flags);
}

void GameHandler::create_renderer(SDL_Window *window, int index, Uint32 flags) {
    this->renderer = SDL_CreateRenderer(window, index, flags);
}

void GameHandler::set_background_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;
}

void GameHandler::set_background_color(SDL_Color color) {
    this->color = color;
}

SDL_Color GameHandler::get_background_color() {
    return this->color;
}

void GameHandler::event_handler() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->set_running(false);
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                // The ESC key
                    case 41:
                        this->set_running(false);
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                Sint32 mouse_x = event.button.x;
                Sint32 mouse_y = event.button.y;

                Tile *temp_tile = (this->get_map())->get_tile_from_position(mouse_x, mouse_y);

                // test tile manipulation on click
                if (event.button.button == 1) {
                    if (temp_tile->is_exposed() == false) {
                        temp_tile->set_exposed(true);
                    }
                }
                else if (event.button.button == 3) {
                    if (temp_tile->is_exposed() == false) {
                        temp_tile->set_flag(!temp_tile->is_flagged());
                    }
                }
                break;
        }
    }
}

void GameHandler::render_logic() {
    // Clear the screen
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderClear(this->renderer);

    // Render the current map
    (this->get_map())->render_map(this->get_renderer());

    // Update the screen
    SDL_RenderPresent(this->renderer);
}

void GameHandler::set_running(bool value) {
    this->running = value;
}

bool GameHandler::is_running() {
    return this->running;
}

SDL_Window *GameHandler::get_window() {
    return this->window;
}

SDL_Renderer *GameHandler::get_renderer() {
    return this->renderer;
}

void GameHandler::create_map() {
    Map *new_map = new Map;

    new_map->create_empty_map();
    new_map->set_bomb_count(0);
    new_map->set_flag_count(0);

    this->map = new_map;
}

Map *GameHandler::get_map() {
    return this->map;
}

void GameHandler::set_fps(unsigned int FPS) {
    this->FPS = FPS;
    this->calculate_frame_delay();
}

unsigned int GameHandler::get_fps() {
    return this->FPS;
}

void GameHandler::calculate_frame_delay() {
    this->frame_delay = 1000 / this->get_fps();
}

void GameHandler::apply_fps_limit() {
    // Limit the gameloop to the set FPS
    Uint32 frame_start = SDL_GetTicks();
    int frame_time = SDL_GetTicks() - frame_start;

    if (this->frame_delay > frame_time) {
        SDL_Delay(this->frame_delay - frame_time);
    }
}

