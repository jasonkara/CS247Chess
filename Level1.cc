#include <vector>
#include <utility>
#include "Level1.h"
#include <time.h>

using namespace std;

Level1::Level1(Board* b, char c) : Player{b, c} {}

bool Level1::playMove() {
    vector<Piece*> myPieces;
	for (int i = 0; i < board->getHeight(); i ++) {
		for (int j = 0; j < board->getWidth(); j ++) {
			Piece* p = board->getLayout().at(i).at(j).get();
			// Only add pieces that are my colour and can make a valid move
			if (p && p->getColour() == colour && !p->getValidMoves().empty()) {
				myPieces.push_back(p);
			}
		}
	}
	// Initialize random number generator
	srand(time(NULL));
	// Choose piece at random
	Piece* chosenPiece = myPieces.at(rand() % myPieces.size());
	Coord start = chosenPiece->getPos();
	// Choose move at random
	int chosenMove = rand() % chosenPiece->getValidMoves().size();
	Coord end = chosenPiece->getValidMoves().at(chosenMove);
	board->movePiece(start, end);

	return true;
}
