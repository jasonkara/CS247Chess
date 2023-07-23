chess: chess.o Board.o Piece.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o Player.o Human.o Level1.o Level2.o Level3.o Level4.o
	g++ chess.o Board.o Piece.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o Player.o Human.o Level1.o Level2.o Level3.o Level4.o -o chess
chess.o: chess.cc Board.h Player.h Human.h Level1.h Level2.h Level3.h Level4.h Piece.h Bishop.h King.h Knight.h Pawn.h Queen.h Rook.h 
	g++ -std=c++14 chess.cc -c
Board.o: Board.cc Board.h Rook.h Pawn.h King.h Queen.h Knight.h Bishop.h
	g++ -std=c++14 Board.cc -c
Piece.o: Piece.cc Piece.h
	g++ -std=c++14 Piece.cc -c 
Bishop.o: Bishop.cc Bishop.h 
	g++ -std=c++14 Bishop.cc -c
King.o: King.cc King.h 
	g++ -std=c++14 King.cc -c
Knight.o: Knight.cc Knight.h
	g++ -std=c++14 Knight.cc -c
Pawn.o: Pawn.cc Pawn.h
	g++ -std=c++14 Pawn.cc -c 
Queen.o: Queen.cc Queen.h
	g++ -std=c++14 Queen.cc -c 
Rook.o: Rook.cc Rook.h
	g++ -std=c++14 Rook.cc -c 
Player.o: Player.cc Player.h
	g++ -std=c++14 Player.cc -c 
Human.o: Human.cc Human.h
	g++ -std=c++14 Human.cc -c 
Level1.o: Level1.cc Level1.h
	g++ -std=c++14 Level1.cc -c 
Level2.o: Level2.cc Level2.h
	g++ -std=c++14 Level2.cc -c 
Level3.o: Level3.cc Level3.h
	g++ -std=c++14 Level3.cc -c 
Level4.o: Level4.cc Level4.h
	g++ -std=c++14 Level4.cc -c 

