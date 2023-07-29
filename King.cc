#include <vector>
#include <tuple>
#include "King.h"
#include "Rook.h"

using namespace std;

King::King(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'K'} {}

vector<Coord> King::getValidMoves() {

    vector<Coord> validMoves;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            Coord candidateMove = {pos.x + dx, pos.y + dy};
            if (board->isValid(candidateMove) &&
                (board->isEmpty(candidateMove) || isOpponent(candidateMove)))
            {
                validMoves.push_back(candidateMove);
            }
            // checkHelper(dx + getPosition().first, dy + getPosition().second, validMoves);
        }
    }

    // check for castle moves
    if (!hasMoved) {
        // right castle
        if (board->isEmpty({pos.x + 1, pos.y}) &&
            board->isEmpty({pos.x + 2, pos.y}))
        {
            Rook* rook = dynamic_cast<Rook*>(board->getPiece({pos.x + 3, pos.y}));
            if (rook != nullptr && !rook->getHasMoved())
                validMoves.push_back({pos.x + 2, pos.y});
        }
        // left castle
        if (board->isEmpty({pos.x - 1, pos.y}) &&
            board->isEmpty({pos.x - 2, pos.y}) &&
            board->isEmpty({pos.x - 3, pos.y}))
        {
            Rook* rook = dynamic_cast<Rook*>(board->getPiece({pos.x - 4, pos.y}));
            if (rook != nullptr && !rook->getHasMoved())
                validMoves.push_back({pos.x - 2, pos.y});
        }
    }


    hasMoved = true;
    return validMoves;
}
