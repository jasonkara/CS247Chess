#include <iostream>

#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

void playerSetup(unique_ptr<Player>& p, string type, Board *b, char c) {
	if (type.substr(0,8) == "computer") {
		if (type.at(8) == '1') {
			p = unique_ptr<Player>(new Level1{b, c});
		} else if (type.at(8) == '2') {
			p = unique_ptr<Player>(new Level2{b, c});
		} else if (type.at(8) == '3') {
			p = unique_ptr<Player>(new Level3{b, c});
		} else {
			p = unique_ptr<Player>(new Level4{b, c});
		}
	} else {
		p = unique_ptr<Player>(new Human{b, c});
	}
}

int main() {
    string cmd;
	unique_ptr<Player> white, black;
	float whiteScore = 0;
	float blackScore = 0;
	bool gameRunning = false;
	unique_ptr<Board> b;

	while (cin >> cmd && cmd != "quit") {
		if (cmd == "setup") {
			if (b.get() == nullptr || white.get() == nullptr) {
				cout << "Please start a new game\n";
			} else if (gameRunning) {
				cout << "A game is currently running. Please end the current game and start a new one to use setup\n";
			} else {
				cout << "You have entered setup mode.\n";
				bool done = false;
				while (!done && cin >> cmd) {
					char second, third, fourth;
					if (cmd == "+") {
						cin >> second >> third >> fourth;
						int x = tolower(third) - 97;
						int y = fourth - 49;
						if (x >= 0 && x < b->getWidth() && y >= 0 && y < b->getHeight()) {
							b->addPiece(x, y, second);
							cout << "Added " << second << " piece at " << third << fourth << endl;
						} else {
							cout << "Invalid coordinate\n";
						}
					} else if (cmd == "-") {
						cin >> second >> third;
						int x = tolower(second) - 97;
						int y = third - 49;
						if (x >= 0 && x < b->getWidth() && y >= 0 && y < b->getHeight()) {
							b->removePiece(x, y);
							cout << "Removed piece at " << second << third << '\n';
						} else {
							cout << "Invalid coordinate\n";
						}
					} else if (cmd == "=") {
						cin >> second;
						second = tolower(second);
						if (second != 'b' && second != 'w') {
							cout << "Invalid colour\n";
						} else {
							b->setCurrentPlayer(second);
							cout << "Changing colour to: " << b->getCurrentPlayer() << '\n';
						}
					} else if (cmd == "done") {
						// check that board is in an acceptable state
						int wKing = 0;
						int bKing = 0;
						bool stopCheck = false;
						for (int i = 0; i < b->getHeight(); i ++) {
							for (int j = 0; j < b->getWidth() && !stopCheck; j ++) {
								const unique_ptr<Piece>& p = b->getLayout()[i][j];
								if (p.get()) { // only check if the piece actually exists
									if (p.get()->getLetter() == 'K') {
										wKing ++;
									} else if (p.get()->getLetter() == 'K') {
										bKing ++;
									} else if (tolower(p.get()->getLetter()) == 'p' && (i == 0 || i == b->getHeight() - 1)) {
										// pawn in the first or last row of the board
										stopCheck = true;
									}
									// TODO - check that kings are not in check
								}
							}
						}
						if (stopCheck) {
							cout << "Please remove all pawns from the first and last row of the board before proceeding.\n";
						} else if (wKing != 1 || bKing != 1) {
							cerr << "num wKing: " << wKing << '\n';
							cerr << "num bKing: " << bKing << '\n';
							cout << "Please ensure there is 1 of each colour of king before proceeding.\n";
						} else {
							done = true;
						}
					}
				}
			}
		} else if (cmd == "game") {
			string type1, type2;
			cin >> type1 >> type2;
			// start a new game
			b = unique_ptr<Board>(new Board{});
			playerSetup(white, type1, b.get(), 'w');
			playerSetup(black, type2, b.get(), 'b');
			cout << *(b.get());
			gameRunning = false;
		} else if (cmd == "resign") {
			// award a point to the other player
			if (b->getCurrentPlayer() == 'w') {
				blackScore += 1;
			} else {
				whiteScore += 1;
			}
			// end the game
			b = std::move(unique_ptr<Board>(nullptr));
		} else if (cmd == "move") {
			if (b.get() == nullptr || white.get() == nullptr) {
				cout << "Please start a new game\n";
			} else {
				if (b->getCurrentPlayer() == 'w') {
					white->playMove();
					b->setCurrentPlayer('b');
				} else {
					black->playMove();
					b->setCurrentPlayer('w');
				}
				cout << *(b.get());
				gameRunning = true;
			}
			// TODO - updating scores on checkmate/stalemate
		}
	}
}
