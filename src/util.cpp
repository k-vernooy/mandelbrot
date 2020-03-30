#include <algorithm>
#include <string>
#include "../include/util.hpp"

using std::string;

int rgb_to_color(int r, int g, int b) {
    vector<int> difs;

    for ( vector<int> set : colors ) {
        difs.push_back(abs(r - set[0]) + abs(g - set[1]) + abs(b - set[2]));
    }

    int x = distance(difs.begin(), min_element(difs.begin(), difs.end()));
    return colors[x][3];
}
