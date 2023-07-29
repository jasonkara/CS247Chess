#ifndef COORD_H
#define COORD_H
#include <string>

// will expand this out later

struct Coord {
    int x, y;
    Coord(int x=0, int y=0);
    Coord(const std::string& pos);
};



#endif 