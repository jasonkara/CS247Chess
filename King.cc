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
    if (!hasMoved && !isInCheck) { // can't castle if king has moved or is in check
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

    // cerr << "king position: " << pos.x << " " << pos.y << endl;
    // cerr << "king valid moves: \n";
    // for (auto move : validMoves) {
    //     cerr << move.x << " " << move.y << endl;
    // }

    return validMoves;
}

bool King::inCheckAtCoord(Coord c) {
    // position
    // cerr << "inCheckAtCoord called" << endl;
    // cerr << pos.x << " " << pos.y << endl;
	for (int i = 0; i < board->getHeight(); i ++) {
		for (int j = 0; j < board->getWidth(); j ++) {
			Piece* p = board->getLayout().at(i).at(j).get();
			if (p && p->getColour() != colour) {
				vector<Coord> moves = p->getValidMoves();
				for (Coord d : moves) {
					if (d.x == c.x && d.y == c.y) return true;
				}
			}
		}
	}
	return false;
}

bool King::inCheck() {
	return inCheckAtCoord(pos);
}

bool King::inCheckmate() {
	if (!inCheck()) return false;
	vector<Coord> moves = getValidMoves();
	for (Coord c : moves) {
		if (!inCheckAtCoord(c)) return false;
	}
	return true;
}

void King::setIsInCheck(bool b) {
    isInCheck = b;
}

void King::setHasMoved(bool b) {
    hasMoved = b;
}
