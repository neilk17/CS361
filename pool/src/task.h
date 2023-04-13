//Mark Boady
//Drexel 2021
//An abstract task class for a thread pool

#ifndef _TASK_H_
#define _TASK_H_

#include <queue>

class task{
    public:
        //These are virtual functions
        //They need to be implemented
        //Returns any new tasks to do
        virtual std::queue<task*>* runTask() = 0;
        //Destructor
        virtual ~task(){}
};
#endif
