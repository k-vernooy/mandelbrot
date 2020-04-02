/*=====================================
 canvas.hpp               modified 4/1
 k-vernooy

 Canvas class definition with coordinate
 storage for positioning and method
 declarations for manipulating view.
=======================================*/


#include <vector>
#include <array>
#include <complex>
#include <map>

using std::vector;
using std::array;
using std::complex;
using std::map;


class Canvas {

    // store a 2d array of ints corresponding to colors
    vector<vector<int> > screen;
    
    // for finding color based on output
    map<int, int> color_map;

    // positioning of canvas
    complex<double> top_left;
    complex<double> bottom_right;

    // size of terminal
    array<int, 2> terminal_dim();

    // get mandelbrot values
    void update_mandelbrot();

    public:

        // transform canvas
        void move(int direction);
        void zoom(bool in);
        
        // screen manipulation
        void clear();
        void draw();
        void reset();
        void render(int width, int height);

        Canvas();
        ~Canvas();
};