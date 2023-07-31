#include <vector>
#include <tuple>
#include "Pawn.h"

using namespace std;

Pawn::Pawn(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'P'}, start_pos{x, y} { }

vector<Coord> Pawn::getValidMoves() {
    vector<Coord> validCoords;
    int direction = (colour == 'w') ? 1 : -1;
    Coord ahead = {pos.x , pos.y + direction};
    Coord attacking1 = {pos.x - 1, pos.y + direction};
    Coord attacking2 = {pos.x + 1, pos.y + direction};

    if (board->isValid(ahead) && board->isEmpty(ahead))
        validCoords.push_back(ahead);
    
    vector<bool> canEnPassents = {false, false}; // whether the pawn can be enpassanted on the left or right
    // cerr << "before" << endl;
    for (int i = -1; i <= 1; i += 2) {
        // cerr << "i: " << i << endl;
        Coord side = {pos.x + i, pos.y};
        // cerr << "after side" << endl;
        if (board->isValid(side) && !board->isEmpty(side) && tolower(board->getPiece(side)->getLetter()) == 'p') {
            // Pawn* test = dynamic_cast<Pawn*>(board->getPiece(side));
            // if (test == nullptr) cerr << "\n\n NULLPTR \n\n" << endl;
            // cerr << "inside" << endl;
            Pawn* side_pawn = static_cast<Pawn*>(board->getPiece(side));
            int j = (i == -1) ? 0 : 1;
            // cerr << "j: " << j << endl;
            canEnPassents[j] = side_pawn->getCanBeEnpassanted();
            // cerr << "canEnPassents[j]: " << canEnPassents[j] << endl;
            // cerr << "after getCanBeEnpassanted" << endl;
        }
        // cerr << "after if" << endl;
    }
    // cerr << "after" << endl;

    
    if (board->isValid(attacking1) &&
        (isOpponent(attacking1) || canEnPassents[0])) 
    {
        validCoords.push_back(attacking1);
    }
    
    if (board->isValid(attacking2) &&
        (isOpponent(attacking2) || canEnPassents[1]))
    {
        validCoords.push_back(attacking2);
    }

    // if the pawn is at its starting position, it can move two spaces ahead
    if (pos.x == start_pos.x && pos.y == start_pos.y) {
        Coord doubleAhead = {pos.x, pos.y + 2 * direction};
        if (board->isEmpty(doubleAhead))
            validCoords.push_back(doubleAhead);
    }

    // print validCoords
    // for (Coord c : validCoords) {
    //     cerr << "(" << c.x << ", " << c.y << ")" << endl;
    // }
    
    return validCoords;
}

void Pawn::setEnPassant(bool b) {
    canBeEnpassanted = b;
}

bool Pawn::getCanBeEnpassanted() {
    return canBeEnpassanted;
}
