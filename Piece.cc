#include <vector>
#include <tuple>
#include <utility>
#include "Piece.h"

using namespace std;

Piece::Piece(Board* b, int x, int y, char c) : board{b}, colour{c}, position{make_pair(x, y)} {}

vector<pair<int,int>> Piece::checkHorizontal() {

}

vector<pair<int,int>> Piece::checkVertical() {

}

vector<pair<int,int>> Piece::checkDiagonal() {

}

pair<int,int> Piece::getPosition() {
    return position;
}

void Piece::setPosition(int x, int y) {
    position = make_pair(x, y);
}

char Piece::getColour() {
    return colour;
}

void Piece::setColour(char c) {
    colour = c;
}

