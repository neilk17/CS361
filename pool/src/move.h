//Mark Boady
//Drexel University 2021

#ifndef _MOVE_H_
#define _MOVE_H_
#include <vector>
#include <iostream>

//Store a move
//The index is where the piece goes
//The char is the move (X or O)
struct move{
	int position;
	char piece;
};

//Print a list of moves
void printMoves(std::vector<move> M);

#endif
