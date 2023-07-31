#include <vector>
#include <utility>
#include <iostream>
#include "Level2.h"
#include <time.h>

using namespace std;

Level2::Level2(Board* b, char c) : Player{b, c} {}

bool Level2::playMove() {
    vector<pair<Coord, Coord>> stdMoves;
	vector<pair<Coord, Coord>> captureMoves;
    vector<pair<Coord, Coord>> checkMoves;
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
	// Initialize random number generator
	srand(time(NULL));
	// Prefer checks, then capturing moves, then any other move
	if (!checkMoves.empty()) {
		int chosenMove = rand() % checkMoves.size();
		board->movePiece(checkMoves[chosenMove].first, checkMoves[chosenMove].second);
	} else if (!captureMoves.empty()) {
		int chosenMove = rand() % captureMoves.size();
		board->movePiece(captureMoves[chosenMove].first, captureMoves[chosenMove].second);
	} else {
		int chosenMove = rand() % stdMoves.size();
		board->movePiece(stdMoves[chosenMove].first, stdMoves[chosenMove].second);
	}

	return true;
}
