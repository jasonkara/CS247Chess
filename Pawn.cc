#include <vector>
#include <tuple>
#include "Pawn.h"

using namespace std;

Pawn::Pawn(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'P'} {}

vector<Coord> Pawn::getValidMoves() {
    vector<Coord> validCoords;
    int direction = (colour == 'w') ? 1 : -1;
    Coord ahead = {pos.x , pos.y + direction};
    Coord attacking1 = {pos.x - 1, pos.y + direction};
    Coord attacking2 = {pos.x + 1, pos.y + direction};

    if (board->isValid(ahead) && board->isEmpty(ahead))
        validCoords.push_back(ahead);
    
    if (board->isValid(attacking1) && isOpponent(attacking1))
        validCoords.push_back(attacking1);
    
    if (board->isValid(attacking2) && isOpponent(attacking2))
        validCoords.push_back(attacking2);

    if (hasDoubleAdvance) {
        Coord doubleAhead = {pos.x, pos.y + 2 * direction};
        if (board->isEmpty(doubleAhead))
            validCoords.push_back(doubleAhead);
        hasDoubleAdvance = false;
    }
    
    return validCoords;
}
