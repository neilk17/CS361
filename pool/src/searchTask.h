//Mark Boady
//Drexel 2021
//A simple search task
#ifndef _SEARCH_TASK_H_
#define _SEARCH_TASK_H_
#include <vector>
#include "task.h"
#include "move.h"
#include "board.h"

class searchTask: public task{
    private:
        std::vector<move> myMoves;
    public:
        //Constructor
        searchTask(std::vector<move> m);
        //Destructor
        ~searchTask();
        //Task to Run
        std::queue<task*>* runTask();
	//Helpers
	private:
		//Print out who won
		void printWinner(board &B);
		//Simulate game and return last move
		char simulate(board &B);
};

#endif

