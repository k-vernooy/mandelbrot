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

double hue_to_rgb(double p, double q, double t) {
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 1.0/6.0) return p + (q - p) * 6.0 * t;
    if(t < 1.0/2.0) return q;
    if(t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
    return p;
}


array<int, 3> hsl_to_rgb(array<double, 3> hsl) {
    double r, g, b;

    if (hsl[1] == 0.0) {
        r = g = b = hsl[2]; // achromatic
    }
    else {
        double q = (hsl[2] < 0.5) ? hsl[2] * (1.0 + hsl[1]) : hsl[2] + hsl[1] - hsl[2] * hsl[1];
        // std::cout << std::endl << "q: " << q << ", " << hsl[2] << std::endl;
        double p = 2.0 * hsl[2] - q;

        r = hue_to_rgb(p, q, hsl[0] + 1.0/3.0);
        g = hue_to_rgb(p, q, hsl[0]);
        b = hue_to_rgb(p, q, hsl[0] - 1.0/3.0);
    }

    return { (int)(r * 255.0), (int)(g * 255.0), (int) (b * 255.0) };
}


array<double, 3> rgb_to_hsl(array<int, 3> rgb) {
    double r = (double) rgb[0] / 255.0;
    double g = (double) rgb[1] / 255.0;
    double b = (double) rgb[2] / 255.0;

    double max = (double)*std::max_element(rgb.begin(), rgb.end()) / 255.0,
           min = (double)*std::min_element(rgb.begin(), rgb.end()) / 255.0;

    double h, s, l = (max + min) / 2.0;

    if (max == min) {
        h = 0.0;
        s = 0.0; // achromatic
    }
    else {
        double d = max - min;
        s = (l > 0.5) ? (d / (2.0 - max - min)) : (d / (max + min));

        if (max == r) h = (g - b) / d + ((g < b) ? 6.0 : 0.0);
        else if (max == g) h = (b - r) / d + 2;
        else h = (r - g) / d + 4;

        h /= 6.0;
    }

    return { h, s, l };
}


array<double, 3> interpolate_hsl(array<double, 3> hsl1, array<double, 3> hsl2, double interpolator) {

    double h,s,l;

    if (hsl1[0] < hsl2[0]) {
        h = hsl1[0] + ((double)(hsl2[0] - hsl1[0]) * interpolator);
    }
    else {
        h = hsl2[0] + ((double)(hsl1[0] - hsl2[0]) * interpolator);
    }

    if (hsl1[1] < hsl2[1]) {
        s = hsl1[1] + ((double)(hsl2[1] - hsl1[1]) * interpolator);
    }
    else {
        s = hsl2[1] + ((double)(hsl1[1] - hsl2[1]) * interpolator);
    }

    if (hsl1[2] < hsl2[2]) {
        l = hsl1[2] + ((double)(hsl2[2] - hsl1[2]) * interpolator);
    }
    else {
        l = hsl2[2] + ((double)(hsl1[2] - hsl2[2]) * interpolator);
    }

    return {h,s,l};
}