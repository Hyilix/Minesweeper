CC = g++
FLAGS = -lSDL2
OBJECTS = main.o GameHandler.o
TARGET = Minesweeper

.PHONY: build run clean

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) -o ./$@ $(OBJECTS)

main.o: main.cpp GameHandler.hpp
	$(CC) $(FLAGS) -c main.cpp

GameHandler.o: GameHandler.cpp GameHandler.hpp
	$(CC) $(FLAGS) -c GameHandler.cpp

clean:
	rm -rf ./$(TARGET) *.o

run: $(TARGET)
	./$(TARGET)
