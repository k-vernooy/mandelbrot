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

    mvprintw(0, 0, std::to_string(size.ws_row).c_str());
    mvprintw(1, 0, std::to_string(size.ws_col).c_str());
    return {size.ws_row - 1, size.ws_col - 1};
}

void Canvas::update_mandelbrot() {
    array<int, 2> dimensions = this->terminal_dim();
    double step_right = (bottom_right.real() - top_left.real()) / (double) dimensions[1];
    double step_down = (top_left.imag() - bottom_right.imag()) / (double) dimensions[0];

    // step_right /= 2.0;
    step_down /= 2.0;

    for (double j = bottom_right.imag(); j < top_left.imag(); j += step_down) {
        vector<int> row;
        for (double i = top_left.real(); i < bottom_right.real(); i += step_right) {
            complex<double> c(i, j);
            row.push_back(mandelbrot(c));
        }
        this->screen.push_back(row);
    }
}


void Canvas::zoom(bool in) {
    double sf = 2;

    if (in) {
        top_left = complex<double> (top_left.real() * (1.0 / sf), top_left.imag() * (1.0 / sf));
        bottom_right = complex<double> (bottom_right.real() * (1.0 / sf), bottom_right.imag() * (1.0 / sf));
    }
    else {
        top_left = complex<double> (top_left.real() * sf, top_left.imag() * sf);
        bottom_right = complex<double> (bottom_right.real() * sf, bottom_right.imag() * sf);
    }
}


void Canvas::move(int dir) {
    array<int, 2> dimensions = this->terminal_dim();
    double step_right = (bottom_right.real() - top_left.real()) / (double) dimensions[1];
    double step_down = (top_left.imag() - bottom_right.imag()) / (double) dimensions[0];

    if (dir == 1) {
        bottom_right = complex<double> (bottom_right.real(), bottom_right.imag() - step_down);
        top_left = complex<double> (top_left.real(), top_left.imag() - step_down);
    }
    else if (dir == 2) {
        bottom_right = complex<double> (bottom_right.real() + step_right, bottom_right.imag());
        top_left = complex<double> (top_left.real() + step_right, top_left.imag());
    }
    else if (dir == 3) {
        bottom_right = complex<double> (bottom_right.real(), bottom_right.imag() + step_down);
        top_left = complex<double> (top_left.real(), top_left.imag() + step_down);
    }
    else if (dir == 4) {
        bottom_right = complex<double> (bottom_right.real() - step_right, bottom_right.imag());
        top_left = complex<double> (top_left.real() - step_right, top_left.imag());
    }
}


void Canvas::clear() {
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            mvprintw(i,j," ");
        }
    }

    this->screen.clear();
}


void Canvas::draw() {
    this->clear();
    this->update_mandelbrot();

    int x = 0;
    int a = 0;

    for (int i = 0; i < screen.size(); i += 2) {
        for (int j = 0; j < screen[i].size(); j++) {
            a++;
            // if (screen[i][j] == MAX_ITERATIONS) {
            attron(COLOR_PAIR(screen[i][j]));
            mvprintw(x,j, "█");
            attroff(COLOR_PAIR(a));
            // }
            // int color = color_map[screen[i][j]];
            // mvprintw(i, j, string("\e[48;5;" + std::to_string(color) + "m").c_str());
        }
        x++;
    }
}


void Canvas::reset() {
    this->top_left = complex<double> (-2.0, 1);
    this->bottom_right = complex<double> (2.0, -1.25);
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

    this->top_left = complex<double> (-2.0, 1);
    this->bottom_right = complex<double> (2.0, -1.25);

    this->color_map = {
        {1, 17},
        {2, 19},
        {MAX_ITERATIONS, 15}
    };

    for (auto& [key, value]: this->color_map) {
        init_pair(key, value, -1);
    }
}


Canvas::~Canvas() {
    endwin();
}