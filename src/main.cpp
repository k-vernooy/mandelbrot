#include "../include/util.hpp"
#include "../include/mandelbrot.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    int width = 200, height = 100;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = (double)(i - (height / 2)) / 50.0;
            double y = (double)(j - (width / 2)) / 50.0;
            // cout << x << ", " << y << ": ";
            complex<double> c(y, x);

            if (mandelbrot(c) == MAX_ITERATIONS) cout << "o";
            else cout << " ";
        }
        cout << endl;
    }
}