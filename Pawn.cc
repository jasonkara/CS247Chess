#include <vector>
#include <tuple>
#include "Pawn.h"

using namespace std;

Pawn::Pawn(Board* b, int x, int y, char c) : Piece{b, x, y, c} {}

vector<tuple<int,int,Piece*>> Pawn::validMoves() {
    
}
