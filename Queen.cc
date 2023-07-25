#include <vector>
#include <tuple>
#include "Queen.h"

using namespace std;

Queen::Queen(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'Q'} {}

vector<tuple<int,int,Piece*>> Queen::validMoves() {
    
}
