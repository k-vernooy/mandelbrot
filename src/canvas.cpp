#include <ncurses.h>
#include <string>

#include "../include/canvas.hpp"
#include "../include/mandelbrot.hpp"

using std::string;


void Canvas::update_mandelbrot() {
    array<int, 2> dimensions = this->terminal_dim();
    double step_right = (bottom_right.real() - top_left.real()) / (double) dimensions[1];
    double step_down = (top_left.imag() - bottom_right.imag()) / (double) dimensions[0];

    for (double i = top_left.real(); i < bottom_right.real(); i += step_right) {
        vector<int> row;
        for (double j = top_left.imag(); j < bottom_right.imag(); j += step_down) {
            complex<double> c(i, j);
            row.push_back(mandelbrot(c));// == MAX_ITERATIONS) row
        }
        this->screen.push_back(row);
    }
}

void Canvas::draw() {
    this->update_mandelbrot();

    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            int color = color_map[screen[i][j]];
            mvprintw(i, j, string("\e[48;5;" + std::to_string(color) + "m").c_str());
        }
    }
}

Canvas::Canvas() {
    setlocale(LC_CTYPE, "");
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    // nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    use_default_colors();
}

Canvas::~Canvas() {
    endwin();
}