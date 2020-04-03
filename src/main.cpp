/*=====================================
 main.cpp                  modified 4/1
 k-vernooy

 Uses ncurses and Canvas class to print
 mandelbrot set to the screen with
 interactive controls.
=======================================*/


#include <iostream>
#include <ncurses.h>
#include <string>

#include "../include/util.hpp"
#include "../include/mandelbrot.hpp"
#include "../include/canvas.hpp"

using std::cout;
using std::endl;
using std::string;


int main() {
    /*
        @desc:
            Driver for the mandelbrot/screen Canvas class.
            Initialize canvas and execute mainloop

        @param: `void`
        @return: `int` status
    */


    // use full 256 color
    putenv("TERM=xterm-256color");

    // get initial frame
    Canvas canvas = Canvas();
    canvas.draw();
    bool stop = false;

    while (!stop) {
        // get keypresses
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
            case 'd':
                canvas.render(600, 800);
                break;
        }

        // print canvas to stdscr
        canvas.draw();
    }
}                     