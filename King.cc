#include <vector>
#include <tuple>
#include "King.h"

using namespace std;

King::King(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'K'} {}

vector<pair<int,int>> King::getValidMoves() {
    
}
