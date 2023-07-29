#include <vector>
#include <tuple>
#include "Knight.h"

using namespace std;

Knight::Knight(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'N'} {    }

vector<Coord> Knight::getValidMoves() {
    vector<Coord> validMoveDiffs = {{-1, -2},
                                    {-1,  2},
                                    { 1,  2},
                                    { 1, -2}};

    cerr << "in knight\n";

    vector<Coord> validMoves;
    for (auto moveDiff : validMoveDiffs) {
        Coord candidateMove = {pos.x + moveDiff.x,  pos.y + moveDiff.y};
        if (board->isValid(candidateMove) && 
            (board->isEmpty(candidateMove) || isOpponent(candidateMove)))
        {
            validMoves.push_back(candidateMove);
        }
    }
    return validMoves;
}
