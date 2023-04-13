#include "move.h"

void printMoves(std::vector<move> M){
	std::cout << "Total Moves: "
		<< M.size()
		<< std::endl;
	for(int i=0; i < M.size(); i++)
	{
		std::cout
			<< "Turn "
			<< (i+1) << ": "
			<< M[i].position
			<< " "
			<< M[i].piece
			<< std::endl;
	}
}
