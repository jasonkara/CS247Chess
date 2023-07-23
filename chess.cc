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

int main() {
    string cmd;

    cin >> cmd;
    // TODO: fill in setup skeleton structure
    if (cmd == "setup") {
        cout << "You have entered setup mode.\n";
        char setup_action;
        while (cin >> setup_action && cmd != "done") {
            char second;
            char third;
            switch (setup_action) {
                case '+':
                    cin >> second >> third;
                    switch (second) {
                        case 'P':
                            cout << "created pawn\n";
                            break;
                        case 'N':
                            cout << "created knight\n";
                            break;
                        case 'B':
                            cout << "created bishop\n";
                            break;
                        case 'R':
                            cout << "created rook\n";
                            break;
                        case 'Q':
                            cout << "created queen\n";
                            break;
                        case 'K':
                            cout << "created king" << endl;
                            break;
                    }
                    break;
                case '-':
                    cin >> second;
                    cout << "remove " << second << '\n';
                    break;
                case '=':
                    cin >> second;
                    cout << "change colour to: " << second << '\n';
                    break;
            }
        }
    }
}
