CXX ?= g++
CXXFLAGS = -I/usr/x86_64-w64-mingw32/include/SDL2
LDFLAGS  = -Wl,-subsystem,console -static-libgcc -static-libstdc++
LDLIBS   = -lSDL2 -lSDL2_ttf

OBJECTS = main.o GameHandler.o Tile.o Map.o Randomiser.o
TARGET  = Minesweeper

ifeq ($(findstring mingw,$(CXX)),mingw)
    TARGET = Minesweeper.exe
endif

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)
