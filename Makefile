BUILD := build
OBJECTS := $(BUILD)/util.o $(BUILD)/mandelbrot.o $(BUILD)/main.o $(BUILD)/canvas.o
HEADERS := include/mandelbrot.hpp include/util.hpp include/canvas.hpp
CC := g++
CV := -std=c++11

all: compile
compile: setup $(OBJECTS)
	$(CC) $(CV) $(OBJECTS) -lncurses -o bin/mandelbrot

# object file targets:
$(BUILD)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CV) $< -c -o $@

setup:
	mkdir -p build bin
