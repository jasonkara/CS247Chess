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
		Player(Board* b, char c);
	public:
		virtual vector<pair<int,int>> getMove() = 0; // Pure virtual - this is an abstract class
		char getColour();
		void setColour(char c);
};

#endif
