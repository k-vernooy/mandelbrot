#include "../include/canvas"
#include <ncurses.h>


Canvas::draw() {
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            int color = color_map[screen[i][j]];
            mvprintw(i, j, "\e[48;5;" + std::to_string(color) + "m");
        }
    }
}

Canvas::Canvas() {
    setlocale(LC_CTYPE, "");
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    use_default_colors();
}

Canvas::~Canvas() {
    endwin();
}