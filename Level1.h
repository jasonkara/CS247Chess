#ifndef LEVEL1_H
#define LEVEL1_H

#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

class Level1 : public Player {
	public:
		Level1(Board* b, char c);
		vector<pair<int,int>> getMove();
};

#endif
