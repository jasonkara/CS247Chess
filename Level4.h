#ifndef LEVEL4_H
#define LEVEL4_H

#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

class Level4 : public Player {
	pair<Coord, Coord> defend();
	public:
		Level4(Board* b, char c);
		bool playMove() override;

};

#endif
