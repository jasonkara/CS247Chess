#include <vector>
#include <memory>
#include <tuple>
#include <utility>
#include "Piece.h"
#include "coord.h"

using namespace std;

Piece::Piece(Board* b, int x, int y, char c, char l) : board{b}, pos{x, y}, colour{c} { 
	// if the colour of the piece is black, the letter should be lowercase
	// if the colour of the piece is white, the letter should be uppercase
	if (tolower(c) == 'b') {
		letter = tolower(l);
	} else {
		letter = toupper(l);
	}
}

bool Piece::isOpponent(Coord coord) const {
    const Piece* const piece = board->getLayout()[coord.y][coord.x].get();
    return (piece != nullptr && 
            piece->colour != this->colour);
}

bool Piece::isUnderAttack() const {
    vector<pair<Coord, Coord>> opponentMoves = board->getOpponentValidMoves();
    for (auto opponentMove : opponentMoves) {
        if (pos.x == opponentMove.second.x &&
            pos.y == opponentMove.second.y) {
                return true;
        }
    }
    return false;
}

bool Piece::isUnderAttackBy(pair<Coord, Coord>& opponent) const {
    vector<pair<Coord, Coord>> opponentMoves = board->getOpponentValidMoves();
    for (auto opponentMove : opponentMoves) {
        if (pos.x == opponentMove.second.x &&
            pos.y == opponentMove.second.y) {
                opponent = opponentMove;
                return true;
        }
    }
    return false;
}

vector<Coord> Piece::checkHelper(int x_diff, int y_diff) const {
    vector<Coord> validMoves;
    for (int direction: {-1, 1}) { // go backwards then forwards
        Coord candidateMove = {pos.x + (direction * x_diff), pos.y + (direction * y_diff)};
        while (board->isValid(candidateMove) && 
            (board->isEmpty(candidateMove) || isOpponent(candidateMove))) 
        {
            // cerr << "candidateMove: " << candidateMove.x << ", " << candidateMove.y << ": accepted\n";
            validMoves.push_back(candidateMove);
            if (isOpponent(candidateMove)) break; // if the piece is an opponent, we can't move past it
            candidateMove.x += direction * x_diff;
            candidateMove.y += direction * y_diff;
        }
    }
    return validMoves;
}

vector<Coord> Piece::checkHorizontal() const {
    return checkHelper(1, 0);
}

vector<Coord> Piece::checkVertical() const {
    return checkHelper(0, 1);
}

vector<Coord> Piece::checkDiagonal() const {
    vector<Coord> leftDiagonal = checkHelper(-1, 1);
    vector<Coord> rightDiagonal = checkHelper(1, 1);
    leftDiagonal.insert(leftDiagonal.end(), rightDiagonal.begin(), rightDiagonal.end());
    return leftDiagonal; // contains both left and right diagonals
}

Coord Piece::getPos() const {
    return pos;
}

void Piece::setPos(Coord coord) {
    pos = coord;
}

char Piece::getColour() const {
    return colour;
}

char Piece::getLetter() const {
    return letter;
}

void Piece::setColour(char c) {
    colour = c;
}

