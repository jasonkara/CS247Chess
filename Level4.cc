#include <vector>
#include <utility>
#include <unordered_map>
#include "Level4.h"

using namespace std;

Level4::Level4(Board* b, char c) : Player{b, c} {}

bool Level4::playMove() {
    pair<Coord, Coord> defensiveMove = defend();

    if (defensiveMove.first.x != -1) {
        cerr << "defensive move: start: " << defensiveMove.first.x << ' ' << defensiveMove.first.y << ' ';
        cerr << "end: " << defensiveMove.second.x << ' ' << defensiveMove.second.y << '\n';
        board->movePiece(defensiveMove.first, defensiveMove.second);
        return true;
    }


    unordered_map<char, int> pieceRanking = {{'p', 1},
                                             {'n', 3},
                                             {'b', 3},
                                             {'r', 5},
                                             {'q', 9}};

    vector<pair<Coord, Coord>> checkMoves;
    vector<pair<Coord, Coord>> captureMoves;
    vector<pair<Coord, Coord>> stdMoves;

    computerHelper(checkMoves, captureMoves, stdMoves);

    // for (auto captureMove : captureMoves) {
    //     cerr << "captureMove: " << captureMove.first.x << ' ' << captureMove.first.y << ' ';
    //     cerr << captureMove.second.x << ' ' << captureMove.second.y << '\n';
    // }

    vector<pair<pair<Coord, Coord>, int>> captureMovesRanking;

    for (auto move : captureMoves) {
        Piece* capturing = board->getPiece(move.first);
        Piece* captured = board->getPiece(move.second);

        int score = pieceRanking[tolower(captured->getLetter())] - pieceRanking[tolower(capturing->getLetter())];
        cerr << "capturing moves: \n";
        cerr << "start: " << move.first.x << ' ' << move.first.y << ' ';
        cerr << "end: " << move.second.x << ' ' << move.second.y << ' ';
        cerr << "score: " << score << '\n';
        captureMovesRanking.push_back(make_pair(move, score));
    }


    // Initialize random number generator
	srand(time(NULL));
	// Prefer checks, then capturing moves, then any other move
	if (!checkMoves.empty()) {
		int chosenMove = rand() % checkMoves.size();
		board->movePiece(checkMoves[chosenMove].first, checkMoves[chosenMove].second);
	} else if (!captureMoves.empty()) {
        int best_score = captureMovesRanking[0].second;
        pair<Coord, Coord> bestMove = captureMovesRanking[0].first;
        for (auto move : captureMovesRanking) {
            if (move.second > best_score) {
                best_score = move.second;
                bestMove = move.first;
            }
        }

        if (best_score < 0 && !stdMoves.empty()) {
            int chosenMove = rand() % stdMoves.size();
            board->movePiece(stdMoves[chosenMove].first, stdMoves[chosenMove].second);
            return true;
        }

        cerr << "best score: " << best_score << endl;
        cerr << "best move: " << bestMove.first.x << ' ' << bestMove.first.y << ' ';
        cerr << "end: " << bestMove.second.x << ' ' << bestMove.second.y << '\n';

		board->movePiece(bestMove.first, bestMove.second);
	} else {
		int chosenMove = rand() % stdMoves.size();
		board->movePiece(stdMoves[chosenMove].first, stdMoves[chosenMove].second);
	}


    return true;
}

pair<Coord, Coord> Level4::defend() {
    unordered_map<char, int> pieceRanking = {{'p', 1},
                                             {'n', 3},
                                             {'b', 3},
                                             {'r', 5},
                                             {'q', 9}};

    vector<Piece*> ourPieces = board->getCurrentPlayerPieces();
    for (Piece* p : ourPieces) {
        pair<Coord, Coord> opponent;
        if (p->isUnderAttackBy(opponent)) {
            Piece* opponent_piece = board->getPiece(opponent.first);
            int score = pieceRanking[tolower(p->getLetter())] - pieceRanking[tolower(opponent_piece->getLetter())];
            if (score < 0) {
                return make_pair(Coord{-1, -1}, Coord{-1, -1});
            }
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