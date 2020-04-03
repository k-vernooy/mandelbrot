/*=====================================
 util.cpp                  modified 4/1
 k-vernooy

 Useful function definitions for color
 conversions and rgb to uint conversions
=======================================*/


#include <algorithm>
#include <string>
#include <iostream>

#include "../include/util.hpp"

using std::array;
using std::string;
using std::vector;


int rgb_to_color(int r, int g, int b) {
    /*
        @desc: converts an rgb color into a 256 terminal color
        @params: `int` r,g,b: color to convert
        @return: `int` 256 color
    */

    vector<int> difs;

    for ( vector<int> set : colors ) {
        // find sum difference between each color channel
        difs.push_back(abs(r - set[0]) + abs(g - set[1]) + abs(b - set[2]));
    }

    // find and return color with smallest sum difference
    int x = distance(difs.begin(), min_element(difs.begin(), difs.end()));
    return colors[x][3];
}


array<int, 3> color_to_rgb(int c) {
    /*
        @desc: converts a 256 terminal color into an rgb color
        @params: `int` c: color to convert
        @return: `std::array<int, 3>` rgb color
    */

    for (vector<int> set : colors) {
        // if color index is what we need, return values
        if (set[3] == c) return {set[0], set[1], set[2]};
    }

    // no color in list matches `c`
    return {-1, -1, -1};
}


Uint32 rgb_to_uint(int r, int g, int b) {
    /*
        @desc: converts rgb seperate values into a Uint32 val
        @params: `int` r, g, b: values to convert
        @return: `Uint32` rgb color
    */

    // bitshift into single value
    Uint32 rgba = (0 << 24) +
                  (r << 16) +
                  (g << 8)  +
                  (b);

    return rgba;
}


array<int, 3> interpolate_rgb(array<int, 3> rgb1, array<int, 3> rgb2, double interpolator) {

    int r = round(rgb1[0] + (double)(rgb2[0] - rgb1[0]) * interpolator);
    int g = round(rgb1[1] + (double)(rgb2[1] - rgb1[1]) * interpolator);
    int b = round(rgb1[2] + (double)(rgb2[2] - rgb1[2]) * interpolator);

    return {r, g, b};
}