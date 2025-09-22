C++ Minesweeper using SDL2
==========================

A small project for learning C++ and SDL2.

This project was aimed as an introductory step towards C++ Object-Oriented Programming and SDL2.

> Feel free to use and modify to your heart's content.

## Settings

The executable can be run with the following flags:
  * `-b *bomb_count*` -> Sets the amount of bombs on the map. Default at `50`.
  * `-w *tiles_width*` -> Sets the amount of tiles on the X axis. Default at `10`.
  * `-h *tiles_height*` -> Sets the amount of tiles on the Y axis. Default at `20`.
  * `--fps *fps_count*` -> Sets the in-game fps. `0` will remove the fps cap. Default at `255`.
  * `--no_fast_reveal` or `-r` -> Disables the fast reveal tile function.
  * `--visible` of `-V` -> Will show all the bombs on the grid. Intended for DEV.

## Building

This game uses SDL2 and SDL2/TTF as dynamically linked libraries. The necessary dll's are present inside the release archive of the game.

In the source code, there is a makefile that builds automatically.

The main compiler used was **gcc/g++** (linux), although other compilers should work just fine if the correct SDL2 files are present.

### Linux

The following will build and run the game:

    make
    ./Minesweeper

### Windows

For Windows compiling, use:

    make CXX=x86_64-w64-mingw32-g++ 

Available .dll files are present for the mingw32 (windows) compiler.
