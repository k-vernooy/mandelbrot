#include "../include/mandelbrot.hpp"

int mandelbrot(complex<double>& c) {
    int i = 0;
    complex<double> z(0,0);
    while (abs(z) <= 2 && i < MAX_ITERATIONS) {
        z = z * z + c;
        i++;
    }

    return i;
}