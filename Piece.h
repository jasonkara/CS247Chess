#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <tuple>
#include <utility>
#include "Board.h"

using namespace std;

// Forward declaration of Board so it compiles
class Board;

class Piece {
	protected:
		Board* board;
		pair<int,int> position;
		char colour;
		vector<pair<int,int>> checkHorizontal();
		vector<pair<int,int>> checkVertical();
		vector<pair<int,int>> checkDiagonal();
	public:
		virtual vector<tuple<int,int,Piece*>> validMoves() = 0; // Pure virtual - this is an abstract class
		pair<int,int> getPosition();
		void setPosition(int x, int y);
		char getColour();
		void setColour(char c);
};

#endif
