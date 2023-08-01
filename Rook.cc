#include <vector>
#include <tuple>
#include "Rook.h"

using namespace std;

Rook::Rook(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'R'} {}

vector<Coord> Rook::getValidMoves() {
    vector<Coord> validMoves = checkHorizontal();
    vector<Coord> vertValidMoves = checkVertical();
    validMoves.insert(validMoves.end(), vertValidMoves.begin(), vertValidMoves.end());
    return validMoves;
}

void Rook::setHasMoved(bool b) {
    hasMoved = b;
}

bool Rook::getHasMoved() const {
    return hasMoved;
}
