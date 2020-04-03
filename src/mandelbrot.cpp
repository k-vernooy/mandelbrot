#include <iostream>
#include "../include/mandelbrot.hpp"

double mandelbrot(complex<double>& c) {
    
    double escape = 3;
    int i = 0;
    complex<double> z(0,0);
    
    while (abs(z) <= escape && i < MAX_ITERATIONS) {
        z = z * z + c;
        i++;
    }

    double su = i + 2 - abs(log2(log(abs(z)) / log(3)));
    if (i == MAX_ITERATIONS) return MAX_ITERATIONS;
    if (su < 0) return 0;

    return su;
}