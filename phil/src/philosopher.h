//Mark Boady
//Drexel University 2021

#ifndef _PHILOSOPHER_H_
#define _PHILOSOPHER_H_

#include <string>
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include "semaphore.h"

class philosopher{
    private:
        int myId;
        semaphore** forks;
    public:
        //Create a new philosopher
        philosopher(int i, semaphore** myForkArray);
        //Thread Instructions
        //This function will be what
        //the thread does
        void run();
    private:
        //Primary Tasks
        //This about life
        void think();
        //Get two forks
        void getForks();
        //Eat some food
        void eat();
        //Put down the forks
        void putForks();
        //Helpers
        void sleepRand(int maxTime);
        //Safe Print
        void display(std::string text);
        //Where is my left fork
        int left();
        //Where is my right fork
        int right();
        
};

#endif
