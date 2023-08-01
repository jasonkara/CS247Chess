#ifndef KING_H
#define KING_H

#include <vector>
#include <tuple>
#include "Piece.h"

using namespace std;

class King : public Piece {
	bool hasMoved = false;
	bool isInCheck = false;
	public:
		King(Board* b, int x, int y, char c);
		vector<Coord> getValidMoves() override;
		bool inCheckAtCoord(Coord c);
		bool inCheck();
		bool inCheckmate();
		void setIsInCheck(bool b);
		void setHasMoved(bool b);
};

#endif
