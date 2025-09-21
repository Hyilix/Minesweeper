#include "Map.hpp"

Tile ***__make_empty_neighbor_map() {
    Tile ***neighbors = new Tile**[3];

    for (unsigned int i = 0; i < 3; i++) {
        neighbors[i] = new Tile*[3];
    }
    return neighbors;
}

Map::Map() {
    std::cout << "Map initialised!" << std::endl;

    this->revealed_tiles = 0;

    unsigned int default_x_size = 5;
    unsigned int default_y_size = 10;

    this->set_universal_tile_size(TILE_Y_SIZE, TILE_X_SIZE);
    this->set_dimensions(default_x_size, default_y_size);

    pair_uint temp_pair(default_x_size, default_y_size);
    this->randomiser = new Randomiser_2D(temp_pair);
}

Map::Map(unsigned int x_size, unsigned int y_size) {
    std::cout << "Map initialised with dimensions: " << std::endl;
    std::cout << x_size << " " << y_size << std::endl;

    this->revealed_tiles = 0;

    this->set_universal_tile_size(TILE_Y_SIZE, TILE_X_SIZE);
    this->set_dimensions(x_size, y_size);

    pair_uint temp_pair(x_size, y_size);
    this->randomiser = new Randomiser_2D(temp_pair);
}

Map::~Map() {
    // Delete all tiles
    for (unsigned int y = 0; y < this->dimensions.second; y++) {
        for (unsigned int x = 0; x < this->dimensions.first; x++) {
            delete this->tiles[y][x];
        }
        delete this->tiles[y];
    }
    delete this->tiles;

}

void Map::create_empty_map() {
    // Create an empty map of Tile objects
    this->tiles = new Tile**[this->dimensions.second];

    for (int i = 0; i < this->dimensions.second; i++) {
        this->tiles[i] = new Tile*[this->dimensions.first];
    }
}

void Map::create_empty_map(std::pair<unsigned int, unsigned int> dimensions) {
    // Create an empty map of Tile objects with specified dimensions
    this->tiles = new Tile**[dimensions.second];

    for (int i = 0; i < dimensions.second; i++) {
        this->tiles[i] = new Tile*[dimensions.first];
    }

    // Save the current dimensions
    this->set_dimensions(dimensions);
}

void Map::create_empty_map(unsigned int width, unsigned int height) {
    // Create an empty map of Tile objects with specified dimensions
    this->tiles = new Tile**[height];

    for (int i = 0; i < height; i++) {
        this->tiles[i] = new Tile*[width];
    }

    // Save the current dimensions
    this->set_dimensions(width, height);
}

void Map::set_dimensions(std::pair<unsigned int, unsigned int> dimensions) {
    this->dimensions = dimensions;
}

void Map::set_dimensions(unsigned int width, unsigned int height) {
    this->dimensions.first = width;
    this->dimensions.second = height;
}

void Map::set_bomb_count(unsigned int count) {
    this->bombs = count;
}

void Map::set_flag_count(unsigned int count) {
    this->flags = count;
}

void Map::set_universal_tile_size(std::pair<unsigned int, unsigned int> size) {
    this->universal_tile_size = size;
}

void Map::set_universal_tile_size(unsigned int width, unsigned int height) {
    this->universal_tile_size.first = width;
    this->universal_tile_size.second = height;
}

std::pair<unsigned int, unsigned int> Map::get_universal_tile_size() {
    return this->universal_tile_size;
}

void Map::fill_map(SDL_Renderer *renderer) {
    unsigned int x_pos = this->get_dimensions().first;
    unsigned int y_pos = this->get_dimensions().second;

    unsigned int x_size = this->get_universal_tile_size().first;
    unsigned int y_size = this->get_universal_tile_size().second;

    for (unsigned int y = 0; y < y_pos; y++) {
        for (unsigned int x = 0; x < x_pos; x++) {
            Tile *temp_tile = new Tile;

            temp_tile->set_size(x_size, y_size);
            temp_tile->set_position(x * x_size, y * y_size);

            temp_tile->create_tile_rectangle();

            this->get_tiles()[y][x] = temp_tile;
            temp_tile->draw_tile(renderer);
        }
    }
}

void Map::render_map(SDL_Renderer *renderer, TTF_Font *font, bool force_draw_bomb) {
    unsigned int x_pos = this->get_dimensions().first;
    unsigned int y_pos = this->get_dimensions().second;

    // unsigned int x_size = this->get_universal_tile_size().first;
    // unsigned int y_size = this->get_universal_tile_size().second;

    for (unsigned int y = 0; y < y_pos; y++) {
        for (unsigned int x = 0; x < x_pos; x++) {
            (this->get_tiles()[y][x])->draw_tile(renderer, font, force_draw_bomb);
        }
    }
}

std::pair<unsigned int, unsigned int> Map::get_dimensions() {
    return this->dimensions;
}

unsigned int Map::get_bomb_count() {
    return this->bombs;
}

unsigned int Map::get_flag_count() {
    return this->flags;
}

Tile ***Map::get_tiles() {
    return this->tiles;
}

std::pair<unsigned int, unsigned int> Map::get_sanitized_position(std::pair<unsigned int, unsigned int> position) {
    unsigned int tile_x_size = this->get_universal_tile_size().first;
    unsigned int tile_y_size = this->get_universal_tile_size().second;

    std::pair<unsigned int, unsigned int> sanitized;

    sanitized.first = position.first / tile_x_size;
    sanitized.second = position.second / tile_y_size;

    return sanitized;
}

std::pair<unsigned int, unsigned int> Map::get_sanitized_position(unsigned int x, unsigned int y) {
    unsigned int tile_x_size = this->get_universal_tile_size().first;
    unsigned int tile_y_size = this->get_universal_tile_size().second;

    std::pair<unsigned int, unsigned int> sanitized;

    sanitized.first = x / tile_x_size;
    sanitized.second = y / tile_y_size;

    return sanitized;
}

Tile *Map::get_tile_from_position(std::pair<unsigned int, unsigned int> position) {
    std::pair<unsigned int, unsigned int> sanitized = this->get_sanitized_position(position);

    unsigned int y_sanitized = sanitized.second;
    unsigned int x_sanitized = sanitized.first;

    return this->get_tiles()[y_sanitized][x_sanitized];
}

Tile *Map::get_tile_from_position(unsigned int x, unsigned int y) {
    std::pair<unsigned int, unsigned int> sanitized = this->get_sanitized_position(x, y);

    unsigned int y_sanitized = sanitized.second;
    unsigned int x_sanitized = sanitized.first;

    return this->get_tiles()[y_sanitized][x_sanitized];
}

Tile ***Map::get_tile_neighbors(std::pair<unsigned int, unsigned int> position) {
    Tile ***neighbors = __make_empty_neighbor_map();
    this->fill_matrix_with_neighbors(neighbors, position);

    return neighbors;
}

Tile ***Map::get_tile_neighbors(unsigned int x_pos, unsigned int y_pos) {
    Tile ***neighbors = __make_empty_neighbor_map();
    pair_uint position(x_pos, y_pos);
    this->fill_matrix_with_neighbors(neighbors, position);

    return neighbors;
}

Tile ***Map::get_tile_neighbors(Tile *tile) {
    auto position = tile->get_raw_position();
    Tile ***neighbors = __make_empty_neighbor_map();
    this->fill_matrix_with_neighbors(neighbors, position);

    return neighbors;
}

Randomiser_2D *Map::get_randomiser() {
    return this->randomiser;
}

void Map::set_bombs(std::vector<pair_uint> bombs) {
    auto bombs_size = bombs.size();

    for (unsigned int i = 0; i < bombs_size; i++) {
        auto current_bomb = bombs[i];
        this->tiles[current_bomb.second][current_bomb.first]->set_bomb(true);

        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                // Skip the tile itself
                if (x == 0 && y == 0) {
                    continue;
                }

                int temp_y_pos = int(current_bomb.second + y);
                int temp_x_pos = int(current_bomb.first + x);
                pair_uint temp_pos(temp_x_pos, temp_y_pos);

                // Out of bounds check
                if (temp_y_pos < 0 || temp_y_pos >= this->dimensions.second ||
                    temp_x_pos < 0 || temp_x_pos >= this->dimensions.first) {
                        continue;
                }

                if (std::find(bombs.begin(), bombs.end(), temp_pos) == bombs.end()) {
                    this->tiles[temp_y_pos][temp_x_pos]->increment_tile_number();
                }
            }
        }
        // this->tiles[current_bomb.second][current_bomb.first]->set_exposed_tile();
    }
}

void Map::open_tiles(std::vector<pair_uint> tiles) {
    auto tiles_size = tiles.size();

    for (unsigned int i = 0; i < tiles_size; i++) {
        auto current_tile = tiles[i];
        Tile *temp_tile = this->tiles[current_tile.second][current_tile.first];
        this->tile_action(temp_tile, LEFT_CLICK);
        // this->tiles[current_tile.second][current_tile.first]->click_action(LEFT_CLICK);
    }
}

void Map::reveal_all_bombs() {
    unsigned int x_pos = this->get_dimensions().first;
    unsigned int y_pos = this->get_dimensions().second;

    // unsigned int x_size = this->get_universal_tile_size().first;
    // unsigned int y_size = this->get_universal_tile_size().second;

    for (unsigned int y = 0; y < y_pos; y++) {
        for (unsigned int x = 0; x < x_pos; x++) {
            Tile *current_tile = this->tiles[y][x];
            if (!current_tile->is_bomb()) {
                if (current_tile->is_flagged()) {
                    current_tile->set_exposed_color(this->tile_wrong_flag);
                    current_tile->set_exposed_tile(true);
                }
            }
            else if (!current_tile->is_flagged()){
                current_tile->set_exposed_tile(true);
            }
        }
    }
}

void Map::tile_action(Tile *tile, uint8_t button) {
    bool bomb_detected = tile->click_action(button, &this->revealed_tiles);

    // if (bomb_pressed != NULL && *bomb_pressed == false) {
    //     *bomb_pressed = bomb_detected;
    // }

    if (bomb_detected) {
        this->game_lost = true;
        return;
    }

    unsigned int y_pos = tile->get_raw_position().second;
    unsigned int x_pos = tile->get_raw_position().first;

    Tile ***neighbors = this->get_tile_neighbors(tile);

    if (button == LEFT_CLICK) {
        // Reveal all bordering tiles with no bombs around them
        // unill reaching a numbered tile
        if (tile->get_tile_number() == 0) {
            for (unsigned int y = 0; y < 3; y++) {
                for (unsigned int x = 0; x < 3; x++) {
                    Tile *temp_tile = neighbors[y][x];

                    if (temp_tile == NULL) {
                        continue;
                    }

                    if (!temp_tile->is_exposed() && !temp_tile->is_flagged()) {
                        this->tile_action(temp_tile, button);
                    }
                }
            }
        }
        // Fast click on an exposed tile with flags around it
        // to reveal all neighbors
        else if (tile->is_exposed()) {
            unsigned int flag_count = this->get_flags_around_tile(neighbors);

            if (flag_count == tile->get_tile_number()) {
                for (unsigned int y = 0; y < 3; y++) {
                    for (unsigned int x = 0; x < 3; x++) {
                        Tile *temp_tile = neighbors[y][x];

                        if (temp_tile == NULL || (y == 0 && x == 0)) {
                            continue;
                        }

                        if (!temp_tile->is_exposed() && !temp_tile->is_flagged()) {
                            // this->tile_action(temp_tile, button);
                            temp_tile->click_action(button, &this->revealed_tiles);
                            std::cout << temp_tile->get_raw_position().first << " " << temp_tile->get_raw_position().second;
                        }
                    }
                }
            }
        }

        for (unsigned int y = 0; y < 3; y++) {
            delete neighbors[y];
        }
        delete neighbors;
    }
}

void Map::fill_matrix_with_neighbors(Tile ***matrix, pair_uint tile_position) {
    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 3; x++) {
            int temp_pos_y = int(tile_position.second + y) - 1;
            int temp_pos_x = int(tile_position.first + x) - 1;

            // Out of bounds check
            if (temp_pos_x < 0 || temp_pos_x >= this->dimensions.first ||
                temp_pos_y < 0 || temp_pos_y >= this->dimensions.second) {
                    matrix[y][x] = NULL;
                    continue;
            }

            matrix[y][x] = this->tiles[temp_pos_y][temp_pos_x];
        }
    }
}

unsigned int Map::get_flags_around_tile(Tile ***neighbors) {
    unsigned int flag_count = 0;
    Tile *central_tile = neighbors[1][1];

    // Tile does not exist
    if (!central_tile) {
        return 0;
    }

    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 3; x++) {
            Tile *temp_tile = neighbors[y][x];

            // Skip central tile and non_existing tiles
            if ((x == 1 && y == 1) || temp_tile == NULL) {
                continue;
            }

            if (temp_tile->is_flagged()) {
                flag_count++;
            }
        }
    }
    return flag_count;
}

void Map::prep_tile_text(SDL_Renderer *renderer, SDL_Color color, TTF_Font *font) {
    unsigned int x_pos = this->get_dimensions().first;
    unsigned int y_pos = this->get_dimensions().second;

    for (unsigned int y = 0; y < y_pos; y++) {
        for (unsigned int x = 0; x < x_pos; x++) {
            tiles[y][x]->prep_text_rendering(renderer, color, font);
        }
    }
}

bool Map::is_game_won() {
    unsigned int tiles = this->dimensions.first * this->dimensions.second;
    tiles -= this->bombs;

    return this->revealed_tiles == tiles;
}

void Map::DEBUG_print_tile_numbers() {
    unsigned int map_size_x = this->dimensions.first;
    unsigned int map_size_y = this->dimensions.second;

    for (unsigned int y = 0; y < map_size_y; y++) {
        for (unsigned int x = 0; x < map_size_x; x++) {
            std::cout << this->tiles[y][x]->get_tile_number() << " ";
        }
    std::cout << std::endl;
    }
}

