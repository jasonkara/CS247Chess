#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <tuple>
#include <utility>
#include "Board.h"
#include "coord.h"

using namespace std;

// Forward declaration of Board so it compiles
class Board;

class Piece {
	protected:
		Board* board;
		Coord pos;
		char colour;
		char letter;

		// returns true if we hit a barrier or out of range
		vector<Coord> checkHelper(int x_diff, int y_diff) const; 
		bool isOpponent(Coord coord) const;

		vector<Coord> checkHorizontal() const;
		vector<Coord> checkVertical() const;
		vector<Coord> checkDiagonal() const;
		char& setLetter(); // used to set letter in derived class
		Piece(Board* b, int x, int y, char c, char l);
	public:
		virtual vector<Coord> getValidMoves() = 0; // Pure virtual - this is an abstract class
		Coord getPos() const;
		void setPos(Coord coord);
		char getColour() const;
		char getLetter() const;
		void setColour(char c);
};

#endif
