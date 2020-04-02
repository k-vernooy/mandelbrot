#include <algorithm>
#include <string>

#include "../include/util.hpp"

using std::array;
using std::string;
using std::vector;


int rgb_to_color(int r, int g, int b) {
    vector<int> difs;

    for ( vector<int> set : colors ) {
        difs.push_back(abs(r - set[0]) + abs(g - set[1]) + abs(b - set[2]));
    }

    int x = distance(difs.begin(), min_element(difs.begin(), difs.end()));
    return colors[x][3];
}


array<int, 3> color_to_rgb(int c) {
    for (vector<int> set : colors) {
        if (set[3] == c) return {set[0], set[1], set[2]};
    }

    return {-1, -1, -1};
}


Uint32 rgb_to_uint(int r, int g, int b) {
    Uint32 rgba = (0 << 24) +
         (r << 16) +
         (g << 8)  +
         b;

    return rgba;
}