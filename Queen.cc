#include <vector>
#include <tuple>
#include "Queen.h"

using namespace std;

Queen::Queen(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'Q'} {}

vector<Coord> Queen::getValidMoves() {
    vector<Coord> validMoves = checkHorizontal();
    vector<Coord> vertValidMoves = checkVertical();
    vector<Coord> diagValidMoves = checkDiagonal();
    validMoves.insert(validMoves.end(), vertValidMoves.begin(), vertValidMoves.end());
    validMoves.insert(validMoves.end(), diagValidMoves.begin(), diagValidMoves.end());
    return validMoves;
}
