/*====================================
 gui.hpp             modified 3/31
 k-vernooy

 Definitions for gui class and
 declarations for methods to render
 the mandelbrot set to an SDL window 
====================================*/

#include <complex>

using std::complex;

class Gui_Window {
    complex<double> top_left;
    complex<double> bottom_right;

    Gui_Window(complex<double> tl, complex<double> br);
};