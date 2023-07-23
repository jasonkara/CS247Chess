#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <iostream>
#include "Piece.h"

using namespace std;

// Forward declaration of Piece so it compiles
class Piece;

class Board {
	vector<vector<unique_ptr<Piece>>> layout;
	char currentPlayer;
	int width;
	int height;
	public:
		Board();
		void makeRow(int y, char c);
		void makePawns(int y, char c);
		void move(int oldX, int oldY, int newX, int newY);
		void addPiece(int x, int y, char type);
		void removePiece(int x, int y);
		friend ostream& operator<<(ostream& o, const Board& b);
		char getCurrentPlayer();
		void setCurrentPlayer(char c);
		vector<vector<unique_ptr<Piece>>>& getLayout();
};

#endif
