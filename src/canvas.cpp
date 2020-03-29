#include <ncurses.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include "../include/canvas.hpp"
#include "../include/mandelbrot.hpp"

using std::string;
using std::cout;
using std::endl;

array<int, 2> Canvas::terminal_dim() {
    struct winsize size;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

    return {size.ws_row - 1, size.ws_col - 1};
}

void Canvas::update_mandelbrot() {
    array<int, 2> dimensions = this->terminal_dim();
    double step_right = (bottom_right.real() - top_left.real()) / (double) dimensions[1];
    double step_down = (top_left.imag() - bottom_right.imag()) / (double) dimensions[0];

    for (double j = bottom_right.imag(); j < top_left.imag(); j += step_down) {
        vector<int> row;
        for (double i = top_left.real(); i < bottom_right.real(); i += step_right) {
            complex<double> c(i, j);
            row.push_back(mandelbrot(c));
        }
        this->screen.push_back(row);
    }
}

void Canvas::draw() {
    this->update_mandelbrot();

    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            if (screen[i][j] == MAX_ITERATIONS) {
                cout << "*";
            }
            else cout << " ";
                // mvprintw(i,j,"*");
            // cout << std::flush;
            // }
            // int color = color_map[screen[i][j]];
            // mvprintw(i, j, string("\e[48;5;" + std::to_string(color) + "m").c_str());
        }
        cout << endl;
    }
}

Canvas::Canvas() {
    // setlocale(LC_CTYPE, "");
    // initscr();
    // noecho();
    // keypad(stdscr, TRUE);
    // // nodelay(stdscr, TRUE);
    // curs_set(0);
    // start_color();
    // use_default_colors();

    this->top_left = complex<double> (-2.0, 2.0);
    this->bottom_right = complex<double> (2.0, -2.0);
}

Canvas::~Canvas() {
    endwin();
}