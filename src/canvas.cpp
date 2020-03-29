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