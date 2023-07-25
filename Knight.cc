#include <vector>
#include <tuple>
#include "Knight.h"

using namespace std;

Knight::Knight(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'N'} {    }

vector<pair<int,int>> Knight::getValidMoves() {
    
}
