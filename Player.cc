#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

Player::Player(Board* b, char c) : board{b}, colour{c} {}

char Player::getColour() {
    return colour;
}

void Player::setColour(char c) {
	colour = c;
}

void Player::computerHelper(vector<pair<Coord, Coord>>& checkMoves,
                   vector<pair<Coord, Coord>>& captureMoves,
                   vector<pair<Coord, Coord>>& stdMoves) 
{
    	for (int i = 0; i < board->getHeight(); i ++) {
		for (int j = 0; j < board->getWidth(); j ++) {
			Piece* p = board->getLayout().at(i).at(j).get();
			// Only check pieces that are my colour
			if (p && p->getColour() == colour) {
				vector<Coord> pieceMoves = p->getValidMoves();
				for (Coord c : pieceMoves) {
					// See if move will place the opposing king in check
					bool isCheckMove = false;
					// Temporarily change position of the piece to end coordinate of the candidate move
					// Then check to see if we can capture a king from that coordinate
					// Finally reset the coordinate back to its original value
					Coord oldCoord = p->getPos();
					p->setPos(c);
					vector<Coord> possibleCheckMoves = p->getValidMoves();
					p->setPos(oldCoord);
					for (Coord checkCoord : possibleCheckMoves) {
						Piece* target = board->getPiece(checkCoord);
						if (target && target->getColour() != colour && tolower(target->getLetter()) == 'k') {
							isCheckMove = true;
						}
					}
					if (isCheckMove) {
						checkMoves.push_back(make_pair(p->getPos(), c));
					} else if (board->getPiece(c)) {
						captureMoves.push_back(make_pair(p->getPos(), c));
					} else {
						stdMoves.push_back(make_pair(p->getPos(), c));
					}
				}
			}
		}
	}
}
