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
	Board b = Board{};

	while (cin >> cmd && cmd != "quit") {
		if (cmd == "setup") {
			cout << "You have entered setup mode.\n";
			while (cin >> cmd && cmd != "done") {
				char second, third, fourth;
				if (cmd == "+") {
					cin >> second >> third >> fourth;
					int x = tolower(third) - 97;
					int y = fourth - 49;
					if (x >= 0 && x < b.getWidth() && y >= 0 && y < b.getHeight()) {
						b.addPiece(x, y, second);
						cout << "Added " << second << " piece at " << third << fourth << endl;
					} else {
						cout << "Invalid coordinate\n";
					}
				} else if (cmd == "-") {
					cin >> second >> third;
					int x = tolower(second) - 97;
					int y = third - 49;
					if (x >= 0 && x < b.getWidth() && y >= 0 && y < b.getHeight()) {
						b.removePiece(x, y);
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
						b.setCurrentPlayer(second);
						cout << "Changing colour to: " << b.getCurrentPlayer() << '\n';
					}
				}
			}
		} else if (cmd == "game") {
			string type1, type2;
			cin >> type1 >> type2;
			playerSetup(white, type1, &b, 'w');
			playerSetup(black, type2, &b, 'b');
			b = Board{};
		} else if (cmd == "resign") {
			// TODO
		} else if (cmd == "move") {
			// TODO
		}
		cout << b; // output text representation of board
	}
}
