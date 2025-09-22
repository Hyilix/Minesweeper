#include "GameHandler.hpp"

GameHandler::GameHandler() {
    std::cout << "Game Handler initialised!" << std::endl;

    // Font prearations
    TTF_Init();
    this->font = TTF_OpenFont(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE);

    this->game_started = false;
    this->game_ended = false;
    this->running = false;
}

GameHandler::~GameHandler() {
    std::cout << "Game Handler Destroyed!" << std::endl;

    // vvv Cleanup functions vvv
    SDL_Quit();
    TTF_CloseFont(this->font);
    TTF_Quit();

    delete this->map;
}

void GameHandler::init(game_settings_t *settings, Uint32 flags) {
    this->settings = settings;
    this->set_fps(settings->fps);

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

    Map *map = this->map;

    while (SDL_PollEvent(&event)) {
        if (this->running == true) {
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

                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (!this->game_ended) {
                        // Raw mouse coordinates
                        Sint32 mouse_x = event.button.x;
                        Sint32 mouse_y = event.button.y;

                        Tile *temp_tile = (this->get_map())->get_tile_from_position(mouse_x, mouse_y);

                        if (this->game_started) {
                            map->tile_action(temp_tile, event.button.button, this->settings->allow_fast_reveal);

                            // Game over
                            if (map->game_lost) {
                                std::cout << "handler bomb pressed" << std::endl;

                                this->get_map()->reveal_all_bombs();
                                SDL_SetWindowTitle(this->window, GAME_OVER_TEXT);
                                this->game_ended = true;
                            }
                        }
                        else {
                            this->game_started = true;

                            Randomiser_2D *randomiser = this->get_map()->get_randomiser();

                            // Prepare the randomiser
                            randomiser->set_random_count(this->get_map()->get_bomb_count());
                            randomiser->set_init_position(temp_tile->get_raw_position());
                            randomiser->apply_grace_to_grid();

                            randomiser->randomise();

                            std::vector<pair_uint> bombs = randomiser->get_bomb_coordinates();
                            this->get_map()->set_bombs(bombs);

                            this->get_map()->prep_tile_text(this->renderer, this->color, this->font);

                            std::vector<pair_uint> tiles = randomiser->get_grace_coordinates();
                            this->get_map()->open_tiles(tiles, this->settings->allow_fast_reveal);

                            // DEBUG PRINT
                            // randomiser->DEBUG_print_grid();
                            // randomiser->DEBUG_print_bombs();
                            // map->DEBUG_print_tile_numbers();

                            delete randomiser;
                        }
                        if (this->get_map()->is_game_won()) {
                            SDL_SetWindowTitle(this->window, GAME_WON_TEXT);
                            this->game_ended = true;
                        }
                        break;
                    }
            }
        }
    }
}

void GameHandler::render_logic() {
    // Clear the screen
    SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderClear(this->renderer);

    // Render the current map
    (this->get_map())->render_map(this->get_renderer(), this->font, this->settings->visible_hidden_bombs);

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
    auto settings = this->settings;
    Map *new_map = new Map(settings->map_x_size, settings->map_y_size);

    new_map->create_empty_map();
    new_map->set_bomb_count(settings->bomb_count);
    new_map->set_flag_count(0);

    new_map->get_randomiser()->set_random_count(settings->bomb_count);

    this->map = new_map;
}

void GameHandler::create_map_debug() {
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
    if (FPS != 0) {
        this->FPS = FPS;
        this->calculate_frame_delay();
    }
}

unsigned int GameHandler::get_fps() {
    return this->FPS;
}

void GameHandler::calculate_frame_delay() {
    this->frame_delay = 1000 / this->get_fps();
}

void GameHandler::apply_fps_limit() {
    // Limit the gameloop to the set FPS
    if (this->FPS != 0) {
        Uint32 frame_start = SDL_GetTicks();
        int frame_time = SDL_GetTicks() - frame_start;

        if (this->frame_delay > frame_time) {
            SDL_Delay(this->frame_delay - frame_time);
        }
    }
}

