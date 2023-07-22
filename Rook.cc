#include <vector>
#include <tuple>
#include "Rook.h"

using namespace std;

Rook::Rook(Board* b, int x, int y, char c) : Piece{b, x, y, c} {}

vector<tuple<int,int,Piece*>> Rook::validMoves() {
    
}
