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
		row.push_back(std::move(unique_ptr<Piece>(new Pawn{this, i, y, c})));
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

void Board::movePiece(Coord start_move, Coord end_move, char promotion) {
	// promotion default to ''. It should only be set if piece to be moved is a pawn and
	// end_move is either the first or last row

	// move piece at start_move to end_move
	layout[end_move.y][end_move.x] = std::move(layout[start_move.y][start_move.x]);
	// update coords in piece
	layout[end_move.y][end_move.x].get()->setPos(end_move);

	// since promotion defaults to Q, this does pawn promotion automatically if the correct move warrants it 
	// (simplifies promotion behavior for bots) 
	Piece* pawn = layout[end_move.y][end_move.x].get();
	if (pawn->getLetter() == 'p' && 
		(end_move.y == 0 || end_move.y == getWidth()-1))
		{
			if (pawn->getColour() == 'W') promotion = toupper(promotion);
			addPiece(end_move.x, end_move.y, promotion);
		}

	// castle special case (king moves 2 squares)
	King* candidateKing = dynamic_cast<King*>(layout[end_move.y][end_move.x].get());

	if (candidateKing) { // if the piece is a king
		// right castle
		if ((end_move.x - start_move.x) == 2) { // if the king moved 2 squares right
			movePiece(Coord{"h1"}, Coord{"f1"}); // move left rook
		// left castle
		} else if ((end_move.x - start_move.x) == -2) { // if the king moved 2 squares left
			movePiece(Coord{"a1"}, Coord{"d1"}); // move right rook
		}
	}

}

void Board::addPiece(int x, int y, char type) {
	char colour = (type > 96) ? 'b' : 'w';
	type = tolower(type);
	if (type == 'p') {
		layout.at(y).at(x) = std::move(unique_ptr<Piece>(new Pawn(this, x, y, colour)));
	} else if (type == 'r') {
		layout.at(y).at(x) = std::move(unique_ptr<Piece>(new Rook(this, x, y, colour)));
	} else if (type == 'n') {
		layout.at(y).at(x) = std::move(unique_ptr<Piece>(new Knight(this, x, y, colour)));
	} else if (type == 'b') {
		layout.at(y).at(x) = std::move(unique_ptr<Piece>(new Bishop(this, x, y, colour)));
	} else if (type == 'q') {
		layout.at(y).at(x) = std::move(unique_ptr<Piece>(new Queen(this, x, y, colour)));
	} else if (type == 'k') {
		layout.at(y).at(x) = std::move(unique_ptr<Piece>(new King(this, x, y, colour)));
	} else {
		cout << "Invalid piece type\n";
	}
}

void Board::removePiece(int x, int y) {
	layout.at(y).at(x) = std::move(unique_ptr<Piece>(nullptr));
}

ostream& operator<<(ostream& out, const Board& b) {
	for (int i = b.height - 1; i >= 0; i--) { // from top to bottom
		out << i+1 << ' '; // output row number
		for (int j = 0; j < b.width; j++) {
			const unique_ptr<Piece>& p = b.layout[i][j];
			if (p.get() != nullptr) { // if piece exists
				out << p.get()->getLetter();
			} else { // if piece doesn't exist, create checkboard pattern
				out << ((i+j) % 2 == 0 ? '_' : ' '); 
			}
		}
		out << '\n';
	}

	// output column number
	out << "\n  ";
	for (char l = 'a'; l < 'a'+b.width; l++) out << l;
	out << '\n';

	return out;
}

char Board::getCurrentPlayer() {
    return currentPlayer;
}

void Board::setCurrentPlayer(char c) {
    currentPlayer = c;
}

int Board::getWidth() const {
	return width;
}

int Board::getHeight() const {
	return height;
}

vector<vector<unique_ptr<Piece>>>& Board::getLayout() {
	return layout;
}

Piece* Board::getPiece(Coord coord) const {
	return (layout[coord.y][coord.x]).get();
}

bool Board::isValid(Coord coord) {
	return (coord.x >= 0 && coord.y >= 0 &&
			coord.x < width && coord.y < height);
}

bool Board::isEmpty(Coord coord) {
	return (layout[coord.y][coord.x].get() == nullptr);
}
