#include <iostream>
#include <string>
#include <getopt.h>

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
    game_settings->fps = 255;

    game_settings->visible_hidden_bombs = false;
    /* ^^^ Default Settings ^^^ */

    static struct option long_options[] = {
        {"fps", required_argument, NULL, 1},
        {"visible", no_argument, NULL, 'V'},
        {"no_fast_reveal", no_argument, NULL, 'r'},
        {0, 0, 0, 0}
    };

    // Handle user settings
    int option_index = 0;
    int option;
    while ((option = getopt_long(argc, argv, "b:w:h:r:V:", long_options, &option_index)) != -1) {
        switch (option) {
            case 'b':
                // Handle bomb count
                game_settings->bomb_count = atoi(optarg);
                break;
            case 'w':
                game_settings->map_x_size = atoi(optarg);
                break;
            case 'h':
                game_settings->map_y_size = atoi(optarg);
                break;
            case 'r':
                game_settings->allow_fast_reveal = false;
                break;
            case 'V':
                game_settings->visible_hidden_bombs = true;
                break;

            case 1:
                // Handle --fps
                game_settings->fps = atoi(optarg);
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
    gamehandler->init(game_settings);
    gamehandler->create_map();

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

