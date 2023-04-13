//Mark Boady
//Drexel University 2021

//A Pool of threads that solve some tasks
#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "task.h"

class threadPool{
    private:
        //How many threads are in our pool
        int numberOfThreads;
        //Pointers to the threads
        std::thread** myThreads;
        //Array to determine if no work left
        bool* status;
        //Exit All
        bool done;
        //Condition Variable
        std::condition_variable needsWork;
        //Mutex to protect queue
        std::mutex queueLock;
        //Queue of Tasks
        std::queue<task*>* toDO;
    public:
        //Constructor
        threadPool();
        //Destructor
        ~threadPool();
        //Add Work to the pool
        void addWork(task* t);
        //Start the pool
        void start();
    private:
        //Thread to do work
        void workerThread(int statusID);
        //Shut Down the Pool
        void stop();
};

#endif
