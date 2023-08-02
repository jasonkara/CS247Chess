#include <vector>
#include <utility>
#include "Level3.h"

using namespace std;

void printMoves(vector<pair<Coord, Coord>>& moves) {
    for (auto move : moves) {
        cout << "start: " << move.first.x << ' ' << move.first.y << ' ';
        cout << "end: " << move.second.x << ' ' << move.second.y << '\n';
    }
}

Level3::Level3(Board* b, char c) : Player{b, c} {}

bool Level3::playMove() {

    // play defensive move if possible
    pair<Coord, Coord> defensiveMove = defend();
    if (defensiveMove.first.x != -1) {
        cerr << "defensive move: start: " << defensiveMove.first.x << ' ' << defensiveMove.first.y << ' ';
        cerr << "end: " << defensiveMove.second.x << ' ' << defensiveMove.second.y << '\n';
        board->movePiece(defensiveMove.first, defensiveMove.second);
        return true;
    }

    // fail back to modified level 2

    vector<pair<Coord, Coord>> opponentValidMoves = board->getOpponentValidMoves();

    // cerr << "made it in playmove" << endl;
    vector<pair<Coord, Coord>> checkMoves;
    vector<pair<Coord, Coord>> captureMoves;
    vector<pair<Coord, Coord>> stdMoves;

    computerHelper(checkMoves, captureMoves, stdMoves);

    vector<pair<Coord, Coord>> moves;

    moves.insert(moves.end(), checkMoves.begin(), checkMoves.end());
    moves.insert(moves.end(), captureMoves.begin(), captureMoves.end());
    moves.insert(moves.end(), stdMoves.begin(), stdMoves.end());

    // print checkMoves
    // cerr << "checkMoves: \n";
    // printMoves(checkMoves);

    // cerr << "captureMoves: \n";
    // printMoves(captureMoves);

    // cerr << "stdMoves: \n";
    // printMoves(stdMoves);

    vector<pair<Coord, Coord>> avoidCapture = removeMoves(checkMoves);
    // cerr << "after first avoidCapture" << endl;
    vector<pair<Coord, Coord>> avoidCapture2 = removeMoves(captureMoves);
    // cerr << "after second avoidCapture" << endl;
    vector<pair<Coord, Coord>> avoidCapture3 = removeMoves(stdMoves);

    // cerr << "after" << endl;


    // cerr << "avoidCapture: \n";
    // printMoves(avoidCapture);
    // cerr << "avoidCapture2: \n";
    // printMoves(avoidCapture2);
    // cerr << "avoidCapture3: \n";
    // printMoves(avoidCapture3);


    // add 
    avoidCapture.insert(avoidCapture.end(), avoidCapture2.begin(), avoidCapture2.end());
    avoidCapture.insert(avoidCapture.end(), avoidCapture3.begin(), avoidCapture3.end());

    // cerr << "avoidCapture: \n";
    // printMoves(avoidCapture);

    // Initialize random number generator
	srand(time(NULL));
	// Prefer checks, then capturing moves, then any other move
	if (!checkMoves.empty()) {
		int chosenMove = rand() % checkMoves.size();
		board->movePiece(checkMoves[chosenMove].first, checkMoves[chosenMove].second);
	} else if (!captureMoves.empty()) {
		int chosenMove = rand() % captureMoves.size();
		board->movePiece(captureMoves[chosenMove].first, captureMoves[chosenMove].second);
	} else if (!stdMoves.empty()) {
		int chosenMove = rand() % stdMoves.size();
		board->movePiece(stdMoves[chosenMove].first, stdMoves[chosenMove].second);
	} else {
        int chosenMove = rand() % avoidCapture.size();
        board->movePiece(avoidCapture[chosenMove].first, avoidCapture[chosenMove].second);
    }
	return true;
}



bool removeMovesHelper(pair<Coord, Coord> move, const vector<pair<Coord, Coord>>& possible_moves) {
    for (auto opponentMove : possible_moves) {
        if (move.second.x == opponentMove.second.x &&
            move.second.y == opponentMove.second.y  ) {
                // cerr << "our moves: start: " << move.first.x << ' ' << move.first.y << ' ';
                // cerr << "end: " << move.second.x << ' ' << move.second.y << '\n';

                // cerr << "opponentMove: start: " << opponentMove.first.x << ' ' << opponentMove.first.y << ' ';
                // cerr << "end: " << opponentMove.second.x << ' ' << opponentMove.second.y << '\n';
                return true;
        }

    }
    return false;
}

vector<pair<Coord, Coord>> Level3::removeMoves(vector<pair<Coord, Coord>>& moves) {
    vector<pair<Coord, Coord>> possibleOpponentMoves = board->getOpponentValidMoves();
    // cerr << "size of opponent moves: " << possibleOpponentMoves.size() << endl;

    // if the end of possibleMoves is equal to the end of possibleOpponentMoves, 
    // then the move can be captured. We delete those moves from possibleMoves
    // and place them a the end
    vector<pair<Coord, Coord>> movesResultingInCapture;
    // cerr << "size of moves: " << moves.size() << endl;
    auto it = moves.begin();
    while (it != moves.end()) {
        // cerr << "repeat\n" << endl;
        if (removeMovesHelper(*it, possibleOpponentMoves)) {
            // cerr << "TRUE\n" << '\n';
            movesResultingInCapture.push_back(*it);
            it = moves.erase(it); // erase invalidates iterator. So we used return iterator
        } else {
            it++;
        }
        // cerr << "our moves: start: " << (*it).first.x << ' ' << (*it).first.y << ' ';
        // cerr << "end: " << (*it).second.x << ' ' << (*it).second.y << '\n';

        // cerr << "opponentMove: start: " << opponentMove.first.x << ' ' << opponentMove.first.y << ' ';
        // cerr << "end: " << opponentMove.second.x << ' ' << opponentMove.second.y << '\n';
    }
    return movesResultingInCapture;
}


pair<Coord, Coord> Level3::defend() {
    vector<Piece*> ourPieces = board->getCurrentPlayerPieces();
    for (Piece* p : ourPieces) {
        if (p->isUnderAttack()) {
            cerr << p->getLetter() << " at " << p->getPos().x << ' ' << p->getPos().y << " is under attack\n";
            vector<Coord> pieceUnderAttackValidMoves = p->getValidMoves();
            Coord oldPos = p->getPos();
            for (Coord c : pieceUnderAttackValidMoves) {
                p->setPos(c); // ghost move
                if (!p->isUnderAttack()) {
                    p->setPos(oldPos); // reset to its original
                    return make_pair(oldPos, c);
                }
            }
        }
    }
    return make_pair(Coord{-1, -1}, Coord{-1, -1});
}




bool Level3::isPieceUnderAttack(Piece* p) {
    Coord piece_pos = p->getPos();
    vector<pair<Coord, Coord>> opponentMoves = board->getOpponentValidMoves();
    
    for (auto move : opponentMoves) {
        if (move.second.x == piece_pos.x && move.second.y == piece_pos.y) {
            return true;
        }
    }
    return false;
}




