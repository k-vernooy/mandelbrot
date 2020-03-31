#include <vector>
#include <array>
#include <complex>
#include <map>

using std::vector;
using std::array;
using std::complex;
using std::map;


class Canvas {
    vector<vector<int> > screen;
    
    map<int, int> color_map;
    complex<double> top_left;
    complex<double> bottom_right;

    array<int, 2> terminal_dim();

    void update_mandelbrot();

    public:
        void move(int direction);
        void zoom(bool in);
        void clear();
        void draw();
        void reset();
        Canvas();
        ~Canvas();
};