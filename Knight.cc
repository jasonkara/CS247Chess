#include <vector>
#include <tuple>
#include "Knight.h"

using namespace std;

Knight::Knight(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'N'} {    }

vector<Coord> Knight::getValidMoves() {
    // vector<pair<int, int>> validMoveDiffs = {{-1, -2},
    //                                          {-1,  2},
    //                                          { 1,  2},
    //                                          { 1, -2}};

    // for (auto p : validMoveDiffs) {
    //     // checkHelper(p.first + getPosition().first, p.second + getPosition().second, validMoves);
    // }
}
