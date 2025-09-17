C++ Minesweeper using SDL2
==========================

A small project for learning C++ and SDL2.

This project was aimed as an introductory step towards C++ Object-Oriented Programming and SDL2.

Things aren't very optimised, and it is not a contender to other more serious Minesweeper applications. 

> Feel free to use and modify to your heart's content.

## Settings

By default, the game will open with a map of **10x20 with 70 bombs**.

The executable can be run with the following flags:
  * -b *bomb_count* -> Sets the amount of bombs on the map
  * -w *tiles_width* -> Sets the amount of tiles on the X axis
  * -h *tiles_height* -> Sets the amount of tiles on the Y axis

## Building

This game uses SDL2 and SDL2/TTF as dynamically linked libraries. The necessary dll's are present inside the release archive of the game.

In the source code, there is a makefile that builds automatically.

The main compiler used was **g++** (linux), although other compilers should work just fine if the correct SDL2 files are present.

### Linux

The following will build and run the game:

    make
    ./Minesweeper

### Windows

For Windows compiling, use:

    make CXX=x86_64-w64-mingw32-g++ 

Available .dll files are present for the mingw32 (windows) compiler.
