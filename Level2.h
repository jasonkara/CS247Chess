#ifndef LEVEL2_H
#define LEVEL2_H

#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

class Level2 : public Player {
	public:
		Level2(Board* b, char c);
		void playMove() override;
};

#endif
