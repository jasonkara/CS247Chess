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

    char promotion;
    for (const auto& coord : validMoves) {
        if (end_move_coord.x == coord.x && end_move_coord.y == coord.y) { // if end move is a valid move
			if (tolower(piece_to_move->getLetter()) == 'k') {
				King* k = dynamic_cast<King*>(piece_to_move);
				if (k->inCheckAtCoord(end_move_coord)) {
					cerr << "You are not allowed to move your king into check. Try again\n";
					return false;
				}
            // handling promotion input
			} else if (piece_to_move->getLetter() == 'p' && 
                      (end_move_coord.y == 0 || end_move_coord.y == board->getWidth() - 1)) 
            {
                cerr << "Enter the letter of the piece you want to promote to (q, r, b, n): \n";
                bool invalidPromotion = false;
                do {
                    cin >> promotion;
                    promotion = tolower(promotion);
                    invalidPromotion = promotion != 'q' && promotion != 'r' && promotion != 'b' && promotion != 'n';
                    if (invalidPromotion) cerr << "Invalid promotion. Try again.\n";
                } while (invalidPromotion);
            }
            board->movePiece(start_move_coord, end_move_coord, promotion);
            return true;
        }
    }
    // piece doesn't exist
    cerr << "Invalid move. Try again\n";
	return false;
}
