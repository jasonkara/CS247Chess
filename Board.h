#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <iostream>
#include "coord.h"
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
		void movePiece(Coord start_move, Coord end_move);
		void addPiece(int x, int y, char type);
		void removePiece(int x, int y);
		friend ostream& operator<<(ostream& out, const Board& b);
		char getCurrentPlayer();
		void setCurrentPlayer(char c);
		int getWidth() const;
		int getHeight() const;
		Piece* getPiece(Coord coord) const ;
		bool isValid(Coord coord); // return if coord is a valid square on the board
		bool isEmpty(Coord coord); // return if coord is empty
		vector<vector<unique_ptr<Piece>>>& getLayout();
};


#endif
