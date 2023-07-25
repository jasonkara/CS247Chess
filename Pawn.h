#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include <tuple>
#include "Piece.h"

using namespace std;

class Pawn : public Piece {
	public:
		Pawn(Board* b, int x, int y, char c);
		vector<pair<int,int>> getValidMoves() override;
};

#endif
