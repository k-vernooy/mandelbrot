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
            case 'q':
                stop = true;
                break;
            case KEY_UP:
                canvas.move(1);
                break;
            case KEY_RIGHT:
                canvas.move(2);
                break;
            case KEY_DOWN:
                canvas.move(3);
                break;
            case KEY_LEFT:
                canvas.move(4);
                break;
            case 'r':
                canvas.reset();
                break;
        }

        canvas.draw();
    }
}