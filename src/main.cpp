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
        cout << std::flush;
        // int ch = getch();
    //     mvprintw(0,0, std::to_string(ch).c_str());
    }

    // int width = 250, height = 100;
    // for (int i = 0; i < height; i += 2) {
    //     for (int j = 0; j < width; j += 1) {
    //         double x = (double)(i - (height / 2)) / 50.0;
    //         double y = (double)(j - (width / 2)) / 50.0;
    //         // cout << x << ", " << y << ": ";
    //         complex<double> c(y, x);

    //         if (mandelbrot(c) == MAX_ITERATIONS) cout << "*";
    //         else cout << " ";
    //     }
    //     cout << endl;
    // }
}