#include <iostream>
#include "../include/mandelbrot.hpp"

double mandelbrot(complex<double>& c) {
    int i = 0;
    complex<double> z(0,0);
    while (abs(z) <= 2 && i < MAX_ITERATIONS) {
        z = z * z + c;
        i++;
    }

    double su = (i - log(log(abs(z)) / log(2)) / log(2.0));    
    if (i == MAX_ITERATIONS) return MAX_ITERATIONS;
    if (su < 0) return 0;

    return su;
}