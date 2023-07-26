#include <vector>
#include <tuple>
#include "King.h"

using namespace std;

King::King(Board* b, int x, int y, char c) : Piece{b, x, y, c, 'K'} {}

vector<pair<int,int>> King::getValidMoves() {

    vector<pair<int, int>> validMoves;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            // need to refactor checkHelper, I'm dumb.
            // checkHelper(dx + getPosition().first, dy + getPosition().second, validMoves);
        }
    }
}
