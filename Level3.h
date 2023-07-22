#ifndef LEVEL3_H
#define LEVEL3_H

#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

class Level3 : public Player {
	public:
		Level3(Board* b, char c);
		vector<pair<int,int>> getMove();
};

#endif
