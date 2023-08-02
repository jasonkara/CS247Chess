#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>
#include "Board.h"

using namespace std;

class Player {
	protected:
		Board* board;
		char colour;
		void computerHelper(vector<pair<Coord, Coord>>& checkMoves,
                   					vector<pair<Coord, Coord>>& captureMoves,
                   					vector<pair<Coord, Coord>>& stdMoves);
		Player(Board* b, char c);
	public:
		virtual bool playMove() = 0; // Pure virtual - this is an abstract class
		char getColour();
		void setColour(char c);
};

#endif
