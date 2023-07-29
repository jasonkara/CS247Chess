#include <vector>
#include <tuple>
#include "Queen.h"

using namespace std;

Queen::Queen(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'Q'} {}

vector<Coord> Queen::getValidMoves() {
    // vector<pair<int, int>> totalMoves = checkHorizontal() const;
    // vector<pair<int, int>> verticalMoves = checkVertical();

    // totalMoves.insert( totalMoves.end(), verticalMoves.begin(), verticalMoves.end() );
    // return totalMoves;
}
