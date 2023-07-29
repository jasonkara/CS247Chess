#include "coord.h"
#include <iostream>
using namespace std;

Coord::Coord(int x, int y) : x{x}, y{y} { }

Coord::Coord(const string& pos) {
    // cerr << "pos[0]: " << pos[0] << '\n';
    // cerr << "pos[1]: " << pos[1] << '\n';

    x = pos[0] - 97;
    y = pos[1] - 49;
    // cerr << "x: " << x << '\n';
    // cerr << "y: " << y << '\n';
}
