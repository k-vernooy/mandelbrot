OBJECTS := build/util.o build/mandelbrot.o build/main.o
CC = g++
CV = std=c++11

all: compile
compile: $(OBJECTS)
	mkdir -p build bin
	$(CC) $(CV) $(OBJECTS) -o bin/mandelbrot

# object file targets:
*/%.o: src/%.cpp
	$(CC) $(CV) $< -c -o $@
