#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <cstdint>
#include <utility>

#define TILE_DEFAULT_SIZE 50

class Tile {
    public:
        Tile();
        ~Tile();

        void click_action();

        std::pair<unsigned int, unsigned int> get_position();
        std::pair<unsigned int, unsigned int> get_size();

        void set_position(std::pair<unsigned int, unsigned int> position);
        void set_position(unsigned int x, unsigned int y);

        void set_size(std::pair<unsigned int, unsigned int> size);
        void set_size(unsigned int width, unsigned int height);

        void set_flag(bool value);
        bool is_flagged();

    private:
        std::pair<unsigned int, unsigned int> position;
        std::pair<unsigned int, unsigned int> size;

        uint8_t tile_number = 0;
        bool has_flag = false;
};

class BombTile : public Tile {
    public:
        BombTile();
        ~BombTile();

    private:
        uint8_t tile_number = 10;
};

#endif
