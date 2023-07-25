#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include <tuple>
#include "Piece.h"

using namespace std;

class Knight : public Piece {
	public:
		Knight(Board* b, int x, int y, char c);
		vector<pair<int,int>> getValidMoves() override;
};

#endif
