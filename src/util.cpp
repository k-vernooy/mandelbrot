/*=====================================
 util.cpp                  modified 4/1
 k-vernooy

 Useful function definitions for color
 conversions and rgb to uint conversions
=======================================*/


#include <algorithm>
#include <string>

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

double hue_to_rgb(int p, int q, int t) {
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 1.0/6.0) return p + (q - p) * 6 * t;
    if(t < 1.0/2.0) return q;
    if(t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
    return p;
}

array<int, 3> hsl_to_rgb(array<int, 3> hsl){
    int r, g, b;

    if (hsl[1] == 0){
        r = hsl[2];
        g = hsl[2];
        b = hsl[2]; // achromatic
    }
    else {
        int q = hsl[2] < 0.5 ? hsl[2] * (1 + hsl[1]) : hsl[2] + hsl[1] - hsl[2] * hsl[1];
        int p = 2 * hsl[2] - q;
        r = hue_to_rgb(p, q, hsl[2] + 1.0/3.0);
        g = hue_to_rgb(p, q, hsl[0]);
        b = hue_to_rgb(p, q, hsl[0] - 1.0/3.0);
    }

    return {(int)round(r * 255), (int)round(g * 255), (int)round(b * 255)};
}

array<int, 3> rgb_to_hsl(array<int, 3> rgb) {
    rgb[0] /= 255, rgb[1] /= 255, rgb[2] /= 255;
    int max = rgb[*std::max_element(rgb.begin(), rgb.end())];
    int min = rgb[*std::min_element(rgb.begin(), rgb.end())];
    int h, s, l = (max + min) / 2;

    if (max == min) {
        h = 0;
        s = 0; // achromatic
    }
    else {
        int d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        
        if (max == rgb[0]) h = (rgb[1] - rgb[2]) / d + (rgb[1] < rgb[2] ? 6 : 0);
        else if (max == rgb[1]) h = (rgb[2] - rgb[0]) / d + 2;
        else h = (rgb[0] - rgb[1]) / d + 4;

        h /= 6;
    }

    return {h, s, l};
}


array<int, 3> interpolate_hsl(array<int, 3> hsl1, array<int, 3> hsl2, double interpolator) {

    int h,s,l;

    if (hsl1[0] < hsl2[0]) {
        h = hsl1[0] + (double)(hsl2[0] - hsl1[0]) * interpolator;
    }
    else {
        h = hsl2[0] + (double)(hsl1[0] - hsl2[0]) * interpolator;
    }

    if (hsl1[1] < hsl2[1]) {
        h = hsl1[1] + (double)(hsl2[1] - hsl1[1]) * interpolator;
    }
    else {
        h = hsl2[1] + (double)(hsl1[1] - hsl2[1]) * interpolator;
    }

    if (hsl1[2] < hsl2[2]) {
        h = hsl1[2] + (double)(hsl2[2] - hsl1[2]) * interpolator;
    }
    else {
        h = hsl2[2] + (double)(hsl1[2] - hsl2[2]) * interpolator;
    }

    return {h,s,l};
}