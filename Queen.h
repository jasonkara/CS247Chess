#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include <tuple>
#include "Piece.h"

using namespace std;

class Queen : public Piece {
	public:
		Queen(Board* b, int x, int y, char c);
		vector<Coord> getValidMoves() override;
};

#endif
