#include <vector>
#include <tuple>
#include "Bishop.h"

using namespace std;

Bishop::Bishop(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'B'} { }

vector<tuple<int,int,Piece*>> Bishop::validMoves() {

}
