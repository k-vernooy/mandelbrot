BUILD = build
OBJECTS := $(BUILD)/util.o $(BUILD)/mandelbrot.o $(BUILD)/main.o
CC = g++
CV = -std=c++11

all: compile
compile: setup $(OBJECTS)
	$(CC) $(CV) $(OBJECTS) -o bin/mandelbrot

# object file targets:
$(BUILD)/%.o: src/%.cpp
	$(CC) $(CV) $< -c -o $@

setup:
	mkdir -p build bin