#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include <tuple>
#include "Piece.h"

using namespace std;

class Rook : public Piece {
	public:
		Rook(Board* b, int x, int y, char c);
		vector<tuple<int,int,Piece*>> validMoves();
};

#endif
