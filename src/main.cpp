#include "../include/util.hpp"
#include "../include/mandelbrot.hpp"
#include "../include/canvas.hpp"
#include <iostream>
#include <ncurses.h>

using std::cout;
using std::endl;

int main() {
    Canvas canvas = Canvas();
    bool stop = false;

    canvas.draw();

    while (!stop) {
        int ch = getch();
        switch (ch) {
            case 'i':
                canvas.zoom(true);
                break;
            case 'o':
                canvas.zoom(false);
                break;
        }

        canvas.draw();
    }
}