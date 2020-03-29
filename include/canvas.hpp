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
    void draw();
    void zoom(bool in);

    public:
        Canvas();
        ~Canvas();
};