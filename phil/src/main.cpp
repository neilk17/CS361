//Mark Boady
//Rendezvous Puzzle Solution

//We have two threads and we want them to meet
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "semaphore.h"
#include "philosopher.h"

int main(int argv, char** argc){
	//Create all
    int numPhil = 5;
    //Make an Array of forks
    semaphore** forks = new semaphore*[numPhil];
    for(int i=0; i < numPhil; i++){
		forks[i] = new semaphore(1);
    }
    
    std::thread* myThreads = new std::thread[numPhil];
    //Create all Threads
    for(int i=0; i < numPhil; i++){
        //Create the Philosopher
        philosopher* p = new philosopher(i, forks);
        //Execute the Object's code
		myThreads[i] = std::thread(
			//Use a Lambda to access the right method
			[](philosopher* m){m->run();}
			//Which Pointer to use
			,p
		);
    }
    //Wait for Program to end
    for(int i=0; i < numPhil; i++){
		myThreads[i].join();
	}
	return 0;
}
