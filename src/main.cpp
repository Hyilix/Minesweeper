#include <iostream>
#include <string>
#include <unistd.h>

#include "GameHandler.hpp"

// TODO: Add timer and bomb/flag count to window title
// TODO: Stop bomb spawning neighboring only bombs
// TODO: Code Cleanup
// TODO: Update README

int main(int argc, char *argv[]) {
    // Pointer to the main gamehandler.
    GameHandler *gamehandler = new GameHandler;

    char gamename[] = "Minesweeper";

    // Create new map settings
    game_settings_t *game_settings = new game_settings_t;

    /* vvv Default Settings vvv */
    game_settings->bomb_count = 50;
    game_settings->map_x_size = 10;
    game_settings->map_y_size = 20;

    game_settings->allow_fast_reveal = true;

    game_settings->visible_hidden_bombs = false;
    /* ^^^ Default Settings ^^^ */

    // Handle user settings
    int option;
    while ((option = getopt(argc, argv, "b:w:h:r:V:")) != -1) {
        switch (option) {
            case 'b':
                game_settings->bomb_count = atoi(optarg);
                break;
            case 'w':
                game_settings->map_x_size = atoi(optarg);
                break;
            case 'h':
                game_settings->map_y_size = atoi(optarg);
                break;
            case 'r':
                game_settings->allow_fast_reveal = str_to_bool(optarg);
                break;
            case 'V':
                game_settings->visible_hidden_bombs = str_to_bool(optarg);
                break;
            case ':':
                std::cout << "option needs a value" << std::endl;
                break;
            case '?':
                std::cout << "unknown option: " << optopt << std::endl;
                break;
        }
    }

    // Initialise and create window / renderer
    gamehandler->init();
    gamehandler->create_map(game_settings);

    // Get window size
    unsigned int window_x_size = (gamehandler->get_map())->get_universal_tile_size().first;
    window_x_size *= (gamehandler->get_map())->get_dimensions().first;

    unsigned int window_y_size = (gamehandler->get_map())->get_universal_tile_size().second;
    window_y_size *= (gamehandler->get_map())->get_dimensions().second;

    // Create window and renderer
    gamehandler->create_window(gamename, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_x_size, window_y_size, 0);
    gamehandler->create_renderer(gamehandler->get_window(), -1, 0);

    gamehandler->set_running(true);

    (gamehandler->get_map())->fill_map(gamehandler->get_renderer());

    // Main gameloop
    while (gamehandler->is_running()) {
        gamehandler->event_handler();
        gamehandler->render_logic();

        gamehandler->apply_fps_limit();
    }

    delete game_settings;
    delete gamehandler;

    return 0;
}

