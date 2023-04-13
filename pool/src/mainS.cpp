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

//Sequential Idea:
int main(int argv, char** argc){
	//Make a Queue of Tasks
    std::queue<task*>* toDoList = new std::queue<task*>();
    //A game starts with no moves made
    std::vector<move> actionList;
    //Put tasks into a queue
    toDoList->push(new searchTask(actionList));
    //Do all the tasks
    while(!toDoList->empty()){
        task* t = toDoList->front();
        toDoList->pop();
        //Run the task
        std::queue<task*>* more = t->runTask();
        while(!more->empty()){
			toDoList->push(more->front());
			more->pop();
        }
    }
    return 0;
}
