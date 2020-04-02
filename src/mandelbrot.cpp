#include <iostream>
#include "../include/mandelbrot.hpp"

double mandelbrot(complex<double>& c) {
    
    int escape = 6;
    int i = 0;
    complex<double> z(0,0);
    
    while (abs(z) <= escape && i < MAX_ITERATIONS) {
        z = z * z + c;
        i++;
    }

    double su = i + 1 - log(log(abs(z))) / log(escape);//(i - log(log(abs(z)) / log(2)) / log(2.0));    
    if (i == MAX_ITERATIONS) return MAX_ITERATIONS;
    if (su < 0) return 0;

    return su;
}