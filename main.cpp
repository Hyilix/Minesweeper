#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include <iostream>

#include "GameHandler.hpp"

GameHandler *gamehandler = new GameHandler;

int main(void) {
    // initialise and create window / renderer
    gamehandler->init();
    gamehandler->create_window("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    gamehandler->create_renderer(gamehandler->get_window(), -1, 0);

    gamehandler->set_running(true);

    // set renderer to color
    // SDL_SetRenderDrawColor(gamehandler->get_renderer(), 255, 0, 0, 0);
    // SDL_RenderClear(gamehandler->get_renderer());
    //
    // // update screen
    // SDL_RenderPresent(gamehandler->get_renderer());
    //
    // // new surface
    // // SDL_Surface *screen_surface = SDL_GetWindowSurface(window);
    // SDL_Rect rectangle = {0, 0, 100, 100};
    //
    // Uint32 color = 255;
    //
    // SDL_SetRenderDrawColor(gamehandler->get_renderer(), 0, 0, 255, 0);
    // SDL_RenderFillRect(gamehandler->get_renderer(), &rectangle);
    // SDL_RenderDrawRect(gamehandler->get_renderer(), &rectangle);
    //
    // SDL_RenderPresent(gamehandler->get_renderer());

    while (gamehandler->is_running()) {
        gamehandler->event_handler();
    }

    delete gamehandler;
    return 0;
}
