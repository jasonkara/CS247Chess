#include <vector>
#include <memory>
#include <iostream>
#include "Board.h"
#include "Rook.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"

using namespace std;

// Helper function for constructor - makes first row of knights, rooks, etc.
void Board::makeRow(int y, char c) {
	vector<unique_ptr<Piece>> row;
	row.push_back(std::move(unique_ptr<Piece>(new Rook{this, 0, y, c})));
	row.push_back(std::move(unique_ptr<Piece>(new Knight{this, 1, y, c})));
	row.push_back(std::move(unique_ptr<Piece>(new Bishop{this, 2, y, c})));
	row.push_back(std::move(unique_ptr<Piece>(new Queen{this, 3, y, c})));
	row.push_back(std::move(unique_ptr<Piece>(new King{this, 4, y, c})));
	row.push_back(std::move(unique_ptr<Piece>(new Bishop{this, 5, y, c})));
	row.push_back(std::move(unique_ptr<Piece>(new Knight{this, 6, y, c})));
	row.push_back(std::move(unique_ptr<Piece>(new Rook{this, 7, y, c})));
	layout.push_back(std::move(row));
	row.clear();
}

// Helper function for constructor - makes second row of pawns
void Board::makePawns(int y, char c) {
	vector<unique_ptr<Piece>> row;
	for (int i = 0; i < 8; i ++) {
		row.push_back(std::move(unique_ptr<Piece>(new Rook{this, i, y, c})));
	}
	layout.push_back(std::move(row));
	row.clear();
}

Board::Board() : currentPlayer{'w'}, width{8}, height{8} {
	// row 1 - assorted white pieces
	makeRow(0, 'w');
	// row 2 - white pawns
	makePawns(1, 'w');
	// rows 3-6 - empty
    vector<unique_ptr<Piece>> row;
	for (int j = 3; j < 7; j ++) {
		for (int i = 0; i < 8; i ++) {
			row.push_back(std::move(unique_ptr<Piece>(nullptr)));
		}
		layout.push_back(std::move(row));
		row.clear();
	}
	// row 7 - black pawns
	makePawns(6, 'b');
	// row 8 - assorted black pieces
	makeRow(7, 'b');
}

void Board::move(int oldX, int oldY, int newX, int newY) {

}

void Board::addPiece(int x, int y, char type) {

}

void Board::removePiece(int x, int y) {

}

ostream& operator<<(ostream& o, const Board& b) {

}

char Board::getCurrentPlayer() {
    return currentPlayer;
}

void Board::setCurrentPlayer(char c) {
    currentPlayer = c;
}

vector<vector<unique_ptr<Piece>>>& Board::getLayout() {
	return layout;
}
