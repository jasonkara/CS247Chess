#include <vector>
#include <utility>
#include "Player.h"

using namespace std;

Player::Player(Board* b, char c) : board{b}, colour{c} {}

char Player::getColour() {
    return colour;
}

void Player::setColour(char c) {
	colour = c;
}
