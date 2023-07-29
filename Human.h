#ifndef HUMAN_H
#define HUMAN_H

#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

class Human : public Player {
	public:
		Human(Board* b, char c);
		void playMove() override;
};

#endif
