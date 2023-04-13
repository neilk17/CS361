//Mark Boady
//Drexel University 2021

//Functions for Simulating the race

#ifndef _RACE_H_
#define _RACE_H_

#include "safeQueue.h"
#include <thread>
//Simulate the Game Master
void gameMaster(
	safeQueue<int>* dice,
	safeQueue<std::thread::id>* winners,
	int players);
	
//Simulate one Racer
void racer(
	safeQueue<int>* dice,
	safeQueue<std::thread::id>* winners);
	
//Sleep between 0 and 2 seconds
void randomSleep();

//Print a Move
void printStatus(int spaces, bool finished);

#endif
