#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include <tuple>
#include "Piece.h"

using namespace std;

class Rook : public Piece {
	bool hasMoved = false;
	public:
		Rook(Board* b, int x, int y, char c);
		bool getHasMoved() const;
		vector<Coord> getValidMoves() override;
};

#endif
