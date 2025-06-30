CC = g++
FLAGS = -lSDL2
OBJECTS = main.o GameHandler.o Tile.o Map.o
TARGET = Minesweeper

.PHONY: build run clean

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) -o ./$@ $(OBJECTS)

main.o: main.cpp GameHandler.hpp
	$(CC) $(FLAGS) -c main.cpp

GameHandler.o: GameHandler.cpp GameHandler.hpp Map.hpp
	$(CC) $(FLAGS) -c GameHandler.cpp

Tile.o: Tile.cpp Tile.hpp
	$(CC) $(FLAGS) -c Tile.cpp

Map.o: Map.cpp Map.hpp Tile.hpp
	$(CC) $(FLAGS) -c Map.cpp

clean:
	rm -rf ./$(TARGET) *.o

run: $(TARGET)
	./$(TARGET)
