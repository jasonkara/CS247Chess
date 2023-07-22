#include <vector>
#include <memory>
#include <iostream>
#include "Board.h"

using namespace std;

Board::Board() : width{8}, height{8}, currentPlayer{'w'} {
    // initialize board with pieces - todo
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
