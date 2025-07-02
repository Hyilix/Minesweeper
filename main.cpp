#include <SDL2/SDL.h>

#include <SDL2/SDL_timer.h>
#include <iostream>

#include "GameHandler.hpp"

GameHandler *gamehandler = new GameHandler;

int main(void) {
    char gamename[] = "Minesweeper";

    // initialise and create window / renderer
    gamehandler->init();
    gamehandler->create_map();

    // get window size
    unsigned int window_x_size = (gamehandler->get_map())->get_universal_tile_size().first;
    window_x_size *= (gamehandler->get_map())->get_dimensions().first;

    unsigned int window_y_size = (gamehandler->get_map())->get_universal_tile_size().second;
    window_y_size *= (gamehandler->get_map())->get_dimensions().second;

    // create window and renderer
    gamehandler->create_window(gamename, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_x_size, window_y_size, 0);
    gamehandler->create_renderer(gamehandler->get_window(), -1, 0);

    gamehandler->set_running(true);

    (gamehandler->get_map())->fill_map(gamehandler->get_renderer());

    Uint32 frame_start;
    int frame_time;

    while (gamehandler->is_running()) {
        frame_start = SDL_GetTicks();

        gamehandler->event_handler();
        gamehandler->render_logic();

        frame_time = SDL_GetTicks() - frame_start;

        if (gamehandler->get_frame_delay() > frame_time) {
            SDL_Delay(gamehandler->get_frame_delay() - frame_time);
        }
    }

    delete gamehandler;
    return 0;
}
