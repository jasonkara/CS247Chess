#include <vector>
#include <utility>
#include "Human.h"

using namespace std;

Human::Human(Board* b, char c) : Player{b, c} {}

void Human::playMove() {
    string start_move;
    string end_move;

    cin >> start_move >> end_move;

    Coord start_move_coord{start_move};
    Coord end_move_coord{end_move};


    // cerr << "start_move: " << start_move << ' ' << "end_move: " << end_move << '\n';
    cerr << "start_move_coord " << start_move_coord.x << ' ' << start_move_coord.y << '\n';

    cerr << "end_move_coord " << end_move_coord.x << ' ' << end_move_coord.y << '\n';

    Piece* piece_to_move = board->getPiece(start_move_coord);
    vector<Coord> validMoves = piece_to_move->getValidMoves();

    for (const auto& coord : validMoves) {
        if (end_move_coord.x == coord.x && end_move_coord.y == coord.y) {
            board->movePiece(start_move_coord, end_move_coord);
            return;
        }
    }
    // piece doesn't exist
    cerr << "Invalid move. Try again\n";

}
