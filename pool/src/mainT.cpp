//Mark Boady

//We have two threads and we want them to meet
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
//Mark Boady
//Drexel 2021
//Thread Pool Example

#include <vector>
#include "task.h"
#include "searchTask.h"
#include "move.h"
#include "threadPool.h"

//Use A Thread Pool Instead
int main(int argv, char** argc){
	//Make a Thread Pool
    threadPool* pool = new threadPool();
    //A game starts with no moves made
    std::vector<move> actionList;
    //Put tasks into a queue
    pool->addWork(new searchTask(actionList));
    //Start up the pool
    pool->start();
    //Exit
    return 0;
}

