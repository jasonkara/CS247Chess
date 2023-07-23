#include <vector>
#include <memory>
#include <tuple>
#include <utility>
#include "Piece.h"

using namespace std;

Piece::Piece(Board* b, int x, int y, char c) : board{b}, position{make_pair(x, y)}, colour{c} {}

// TODO: there is probably a better way to do this

bool Piece::checkHelper(int x, int y, const Piece* const piece, vector<pair<int, int>>& validMoves) {
    bool ret = true;
    if (piece != nullptr) {
        if (piece->colour != colour) ret = false;
        else return false;
    }
    validMoves.push_back(make_pair(x, y));
    return ret;
}

vector<pair<int,int>> Piece::checkHorizontal() {
    const vector<unique_ptr<Piece>>& row = board->getLayout()[position.second];

    vector<pair<int, int>> validMoves;
    // check to the right
    for (int i = position.first + 1; i < board->getWidth(); i++) {
        bool cont = checkHelper(i, position.second, row[i].get(), validMoves);
        if (!cont) break;
    }

    for (int i = position.first - 1; i >= 0; i--) {
        bool cont = checkHelper(i, position.second, row[i].get(), validMoves);
        if (!cont) break;
    }
    return validMoves;
}

vector<pair<int,int>> Piece::checkVertical() {
    const vector<vector<unique_ptr<Piece>>>& layout = board->getLayout();
    vector<pair<int, int>> validMoves;
    for (int i = position.second + 1; i < board->getHeight(); i++) {
        bool cont = checkHelper(position.first, i, layout[i][position.first].get(), validMoves);
        if (!cont) break;
    }
    for (int i = position.second - 1; i >= 0; i++) {
        bool cont = checkHelper(position.first, i, layout[i][position.first].get(), validMoves);
        if (!cont) break;
    }
    
}

vector<pair<int,int>> Piece::checkDiagonal() {
    int x = position.first + 1;
    int y = position.second + 1;
    vector<pair<int, int>> validMoves;
    

    while (x <= board->getWidth() && y <= board->getHeight()) {
        bool cont = checkHelper(x, y, board->getLayout()[y][x].get(), validMoves);
        if (!cont) break;
        x++;
        y++;
    }

    x = position.first - 1;
    y = position.second - 1;
    while (x <= board->getWidth() && y <= board->getHeight()) {
        bool cont = checkHelper(x, y, board->getLayout()[y][x].get(), validMoves);
        if (!cont) break;
        x--;
        y--;
    }
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

