#include <vector>
#include <tuple>
#include "Pawn.h"

using namespace std;

Pawn::Pawn(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'P'} {}

vector<pair<int,int>> Pawn::getValidMoves() {
    
}
