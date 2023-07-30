#include <vector>
#include <utility>
#include "Human.h"
#include "King.h"

using namespace std;

Human::Human(Board* b, char c) : Player{b, c} {}

bool Human::playMove() {
    string start_move;
    string end_move;

    cin >> start_move >> end_move;

    Coord start_move_coord{start_move};
    Coord end_move_coord{end_move};


    // cerr << "start_move: " << start_move << ' ' << "end_move: " << end_move << '\n';
    // cerr << "start_move_coord " << start_move_coord.x << ' ' << start_move_coord.y << '\n';

    // cerr << "end_move_coord " << end_move_coord.x << ' ' << end_move_coord.y << '\n';

    Piece* piece_to_move = board->getPiece(start_move_coord);

	// Make sure a piece exists there
	if (!piece_to_move) {
		cerr << "No piece at that position. Try again\n";
		return false;
	}

	// Make sure one player can't move the other player's pieces
	if (piece_to_move->getColour() != colour) {
		cerr << "That piece belongs to a different player. Try again\n";
		return false;
	}
    vector<Coord> validMoves = piece_to_move->getValidMoves();

    for (const auto& coord : validMoves) {
        if (end_move_coord.x == coord.x && end_move_coord.y == coord.y) {
			if (tolower(piece_to_move->getLetter()) == 'k') {
				King* k = dynamic_cast<King*>(piece_to_move);
				if (k->inCheckAtCoord(end_move_coord)) {
					cerr << "You are not allowed to move your king into check. Try again\n";
					return false;
				}
			}
            board->movePiece(start_move_coord, end_move_coord);
            return true;
        }
    }
    // piece doesn't exist
    cerr << "Invalid move. Try again\n";
	return false;
}
