#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include <tuple>
#include "Piece.h"

using namespace std;

class Bishop : public Piece {
	public:
		Bishop(Board* b, int x, int y, char c);
		vector<tuple<int,int,Piece*>> validMoves();
};

#endif
