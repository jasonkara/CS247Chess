#ifndef LEVEL3_H
#define LEVEL3_H

#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

class Level3 : public Player {
	vector<pair<Coord, Coord>> removeMoves(vector<pair<Coord, Coord>>& moves);
	void getLevel2Moves(vector<pair<Coord, Coord>>& checkMoves,
                        vector<pair<Coord, Coord>>& captureMoves,
                        vector<pair<Coord, Coord>>& stdMoves);

	pair<Coord, Coord> defend(const vector<pair<Coord, Coord>>& moves);
	bool isPieceUnderAttack(Piece* p);
	pair<Coord, Coord> defend();

	public:
		Level3(Board* b, char c);
		bool playMove() override;
};

#endif
