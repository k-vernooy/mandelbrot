/*=====================================
 canvas.cpp               modified 3/31
 k-vernooy

 Canvas class methods for writing,
 printing, and manipulating the screen,
 and calculating/coloring the mandelbrot
 set
=======================================*/


#include <ncurses.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "../include/util.hpp"
#include "../include/canvas.hpp"
#include "../include/mandelbrot.hpp"

using std::string;
using std::cout;
using std::endl;


array<int, 2> Canvas::terminal_dim() {
    /*
        @desc: retrieves the current dimensions of the terminal
        @params: none
        @return: `array<int, 2>` size of terminal in format {rows, columns}
    */

    struct winsize size;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
    return {size.ws_row - 1, size.ws_col - 1};
}


void Canvas::update_mandelbrot() {
    /*
        @desc: calculates values of mandelbrot iteration for each coordinate 
        @params: none
        @return: `void`
    */


    array<int, 2> dimensions = this->terminal_dim();

    // get amount by which coordinates step per character on screen
    double step_right = (bottom_right.real() - top_left.real()) / (double) dimensions[1];
    double step_down = (top_left.imag() - bottom_right.imag()) / (double) dimensions[0];

    // for resolution doubling trick
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


void Canvas::render(int width, int height) {
    /*
        @desc:
            Create an SDL window and print the colored
            mandelbrot set to it with gradient shading.
        
        @params:
            `int` width: width of screen
            `int` height: height of screen

        @return: `void`
    */

    vector<vector<double> > scr;

    // get amount by which coordinates step per character on screen
    double step_right = (bottom_right.real() - top_left.real()) / (double) width;
    double step_down = (top_left.imag() - bottom_right.imag()) / (double) height;


    for (double j = bottom_right.imag(); j < top_left.imag(); j += step_down) {
        vector<double> row;
        for (double i = top_left.real(); i < bottom_right.real(); i += step_right) {
            complex<double> c(i, j);
            row.push_back(mandelbrot(c));
        }
        scr.push_back(row);
    }

    Uint32* background = new Uint32[width * height];

    int i = 0;
    for (vector<double> row : scr) {
        int j = 0;
        for (double val : row) {
            val /= 3.0;

            if (val == MAX_ITERATIONS / 3.0) {
                background[(width * i) + j] = rgb_to_uint(0,0,0);
            }
            else {
                double interpolator = (val - floor(val));
                array<int, 3> ar1 = color_to_rgb(this->color_map[floor(val)]);
                array<int, 3> ar2 = color_to_rgb(this->color_map[floor(val) + 1]);
                array<int, 3> rgb = interpolate_rgb(ar1, ar2, interpolator);

                Uint32 x = rgb_to_uint(rgb[0], rgb[1], rgb[2]);
                background[(width * i) + j] = x;
            }

            j++;
        }
        i++;
    }

    // initialize window
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    SDL_Window* window = SDL_CreateWindow("Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_UpdateTexture(texture, NULL, background, width * sizeof(Uint32));

    bool quit = false;

    while (!quit) {
        SDL_UpdateTexture(texture, NULL, background, width * sizeof(Uint32));
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) quit = true;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // destroy arrays and SDL objects
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit();
}


void Canvas::zoom(bool in) {
    /*
        @desc: zooms in or out on the canvas
        @params: `bool` in: whether or not to zoom in
        @return: `void`
    */

    // get scale factor (in/out)
    double sf = 2.0;
    if (in) sf = 0.5;

    // find center by midpoint of corners
    complex<double> center(
            (top_left.real() + bottom_right.real()) / 2.0, 
            (top_left.imag() + bottom_right.imag()) / 2.0
        );


    // multiply distance from center by `sf`
    top_left = complex<double> (
            center.real() - ((center.real() - top_left.real()) * sf),
            center.imag() - ((center.imag() - top_left.imag()) * sf)
        );

    bottom_right = complex<double> (
            center.real() - ((center.real() - bottom_right.real()) * sf),
            center.imag() - ((center.imag() - bottom_right.imag()) * sf)
        );
}


void Canvas::move(int dir) {
    /*
        @desc: translate canvas up, down, left, right
        @params: `int` dir: direction to move in - 1 up, 2 right, 3 down, 4 left
        @return: `void`
    */

    // get {width, height} of terminal
    array<int, 2> dimensions = this->terminal_dim();
    
    // determine how much scope changes per fullblock character change
    double step_right = (bottom_right.real() - top_left.real()) / (double) dimensions[1];
    double step_down = (top_left.imag() - bottom_right.imag()) / (double) dimensions[0];


    if (dir == 1) {
        // translate up with subtraction of step_down
        bottom_right = complex<double> (bottom_right.real(), bottom_right.imag() - step_down);
        top_left = complex<double> (top_left.real(), top_left.imag() - step_down);
    }
    else if (dir == 2) {
        // translate right with addition of step_right
        bottom_right = complex<double> (bottom_right.real() + step_right, bottom_right.imag());
        top_left = complex<double> (top_left.real() + step_right, top_left.imag());
    }
    else if (dir == 3) {
        // translate down with addition of step_down
        bottom_right = complex<double> (bottom_right.real(), bottom_right.imag() + step_down);
        top_left = complex<double> (top_left.real(), top_left.imag() + step_down);
    }
    else if (dir == 4) {
        // translate left with subtraction of step_right
        bottom_right = complex<double> (bottom_right.real() - step_right, bottom_right.imag());
        top_left = complex<double> (top_left.real() - step_right, top_left.imag());
    }

    return;
}


void Canvas::clear() {
    /*
        @desc: clears the screen's canvas and prints empty chars
        @params: none
        @return: `void`
    */

    // print characters to clear the screen
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            mvprintw(i,j," ");
        }
    }

    // clear screen vector
    this->screen.clear();
    return;

}


void Canvas::draw() {
    /*
        @desc:
            prints the contents of the @attr `screen`
            with color coding from the @attr `color_map`

        @params: none
        @return: `void`
    */

    this->clear();
    this->update_mandelbrot();

    int x = 0, a = 1;

    for (int i = 0; i < screen.size(); i += 2) {
        for (int j = 0; j < screen[i].size(); j++) {
            // set correct color
            attron(COLOR_PAIR(screen[i][j] + 1));
            mvprintw(x,j, "█");
            // remove color
            attroff(COLOR_PAIR(a));
            a++;
        }
        x++;
    }
}


void Canvas::reset() {
    /*
        @desc: returns the canvas to default coordinates
        @params: none
        @return: void
    */

    // set coordinates to their initial default
    this->top_left = complex<double> (-2.0, 1);
    this->bottom_right = complex<double> (2.0, -1.25);
}


Canvas::Canvas() {
    /*
        @desc:
            initializes curses window, sets
            default coords, initializes color_map

        @params: none
        @return: none
    */

    // set default coordinates
    // TODO: scale based on terminal dim
    array<int, 2> dim = this->terminal_dim(); // {height, width}
    double r = 0.55;
    dim[1] = r * dim[1];

    if (dim[0] > dim[1]) {
        double ratio = (double) dim[0] / (double) dim[1];
        this->top_left = complex<double> (-2.0, 2.0 * ratio);
        this->bottom_right = complex<double> (2.0, -2.0 * ratio);
    }
    else {
        double ratio = (double) dim[1] / (double) dim[0];
        this->top_left = complex<double> (-2.0 * ratio, 2.0);
        this->bottom_right = complex<double> (2.0 * ratio, -2.0);
    }
    
    // init curses
    setlocale(LC_CTYPE, "");
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();


    this->color_map = {
        {0, 202},
        {1, 202},
        {2, 208},
        {3, 214},
        {4, 220},
        {5, 220},
        {6, 220},
        {7, 226},
        {8, 226},
        {9, 227},
        {10, 190},
        {11, 154},
        {12, 118},
        {13, 46},
        {14, 76},
        {15, 2},
        {16, 41},
        {17, 42},
        {18, 72},
        {19, 30},
        {20, 33},
        {21, 21},
        {22, 20},
        {23, 19},
        {24, 19},
        {25, 54},
        {26, 55},
        {27, 57},
        {28, 92},
        {29, 129},
        {30, 127},
        {31, 125},
        {32, 124},
        {33, 160},
        {34, 196},
        {35, 202},
        {36, 208},
        {37, 214},
        {38, 220},
        {39, 220},
        {40, 221},
        {41, 222},
        {42, 227},
        {43, 226},
        {44, 226},
        {45, 190},
        {46, 154},
        {47, 118},
        {48, 46},
        {49, 76},
        {50, 2},
        {51, 41},
        {52, 42},
        {53, 72},
        {54, 30},
        {55, 33},
        {56, 21},
        {57, 20},
        {58, 19},
        {59, 19},
        {60, 54},
        {61, 55},
        {62, 57},
        {63, 92},
        {64, 129},
        {65, 127},
        {66, 125},
        {67, 124},
        {68, 160},
        {69, 196},
        {70, 202},
        {71, 208},
        {72, 214},
        {73, 220},
        {74, 220},
        {75, 221},
        {76, 222},
        {77, 227},
        {78, 226},
        {79, 226},
        {80, 190},
        {81, 154},
        {82, 118},
        {83, 46},
        {84, 76},
        {85, 2},
        {86, 41},
        {87, 42},
        {88, 72},
        {89, 30},
        {90, 33},
        {91, 21},
        {92, 20},
        {93, 19},
        {94, 19},
        {95, 196},
        {96, 202},
        {97, 208},
        {98, 214},
        {99, 220},
        {100, 220},
        {101, 221},
        {102, 222},
        {103, 227},
        {104, 226},
        {105, 226},
        {106, 190},
        {107, 154},
        {108, 118},
        {109, 46},
        {110, 76},
        {111, 2},
        {112, 41},
        {113, 42},
        {114, 72},
        {115, 30},
        {116, 33},
        {117, 21},
        {118, 20},
        {119, 19},
        {120, 19},
        {121, 196},
        {MAX_ITERATIONS, 16}
    };


    for (auto& [key, value]: this->color_map) {
        init_pair(key + 1, value, -1);
    }
}


Canvas::~Canvas() {
    /*
        @desc: cleans up ncurses
        @params: none
        @return: void
    */

    endwin();
}