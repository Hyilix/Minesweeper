CXX ?= g++
CXXFLAGS = -I/usr/x86_64-w64-mingw32/include/SDL2
LDFLAGS  =
LDLIBS   = -lSDL2 -lSDL2_ttf

OBJECTS = main.o GameHandler.o Tile.o Map.o Randomiser.o
TARGET  = Minesweeper
TARGET_WIN = Minesweeper.exe

ifeq ($(findstring mingw,$(CXX)),mingw)
	TARGET = $(TARGET_WIN)
	LDFLAGS  = -Wl,-subsystem,console -static-libgcc -static-libstdc++
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
	rm -f $(TARGET_WIN) *.o

run: $(TARGET)
	./$(TARGET)
