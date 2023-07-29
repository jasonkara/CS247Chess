#include <vector>
#include <memory>
#include <tuple>
#include <utility>
#include "Piece.h"
#include "coord.h"

using namespace std;

Piece::Piece(Board* b, int x, int y, char c, char l) : board{b}, position{x, y}, colour{c} { 
	// if the colour of the piece is black, the letter should be lowercase
	// if the colour of the piece is white, the letter should be uppercase
	if (tolower(c) == 'b') {
		letter = tolower(l);
	} else {
		letter = toupper(l);
	}
}

// TODO: there is probably a better way to do this

bool Piece::checkHelper(Coord coord, vector<Coord>& validMoves) {
    // range check
    if (coord.x < 0 || coord.y >= board->getWidth() ||
        coord.y < 0 || coord.y >= board->getHeight())
    {
        return true;
    }

    const Piece* const piece = board->getLayout()[coord.x][coord.y].get();

    // hit check
    if (piece != nullptr) {
        if (piece->colour != colour) validMoves.push_back(coord); // only push_back if it's the opponents piece
        return true;
    }

    validMoves.push_back(coord);
    return false;
}

bool Piece::isOpponent(Coord coord) const {
    const Piece* const piece = board->getLayout()[coord.y][coord.x].get();
    return (piece != nullptr && 
            piece->colour != this->colour);
}

vector<Coord> Piece::checkHorizontal() const {
    // const vector<unique_ptr<Piece>>& row = board->getLayout()[position.second];

    // vector<pair<int, int>> validMoves;
    // // check the right squares of current piece
    // for (int i = position.first + 1; i < board->getWidth(); i++) {
    //     bool cont = checkHelper(i, position.second, row[i].get(), validMoves);
    //     if (!cont) break;
    // }

    // // check to the left squares of current piece
    // for (int i = position.first - 1; i >= 0; i--) {
    //     bool cont = checkHelper(i, position.second, row[i].get(), validMoves);
    //     if (!cont) break;
    // }
    // return validMoves;
}

vector<Coord> Piece::checkVertical() const {
    const vector<vector<unique_ptr<Piece>>>& layout = board->getLayout();
    // vector<pair<int, int>> validMoves;
    // for (int i = position.second + 1; i < board->getHeight(); i++) {
    //     bool cont = checkHelper(position.first, i, layout[i][position.first].get(), validMoves);
    //     if (!cont) break;
    // }
    // for (int i = position.second - 1; i >= 0; i++) {
    //     bool cont = checkHelper(position.first, i, layout[i][position.first].get(), validMoves);
    //     if (!cont) break;
    // }
    
}

vector<Coord> Piece::checkDiagonal() const {
    // int x = position.first + 1;
    // int y = position.second + 1;
    // vector<pair<int, int>> validMoves;
    

    // while (x <= board->getWidth() && y <= board->getHeight()) {
    //     bool cont = checkHelper(x, y, board->getLayout()[y][x].get(), validMoves);
    //     if (!cont) break;
    //     x++;
    //     y++;
    // }

    // x = position.first - 1;
    // y = position.second - 1;
    // while (x <= board->getWidth() && y <= board->getHeight()) {
    //     bool cont = checkHelper(x, y, board->getLayout()[y][x].get(), validMoves);
    //     if (!cont) break;
    //     x--;
    //     y--;
    // }
}

Coord Piece::getPosition() const {
    return position;
}

void Piece::setPosition(Coord coord) {
    position = coord;
}

char Piece::getColour() const {
    return colour;
}

char Piece::getLetter() const {
    return letter;
}

void Piece::setColour(char c) {
    colour = c;
}

