//Mark Boady
//Drexel University 2021

#include "race.h"
#include <thread>
#include <iostream>

//Racer and Game Master Implementations

//Simulate the Game Master
void gameMaster(
	safeQueue<int>* dice,
	safeQueue<std::thread::id>* winners,
	int players)
{
	while(winners->length() != players){
		//Step 1: select a random number between 0 and 5
		int k = std::rand()%6;
		//Step 2: Roll k dice
		for(int i=0; i < k; i++){
			int roll = std::rand()%6+1;
			//Step 3: Add to queue
			dice->push(roll);
		}
		//Sleep
		randomSleep();
	}
}
	
//Simulate one Racer
void racer(
	safeQueue<int>* dice,
	safeQueue<std::thread::id>* winners)
{
	int position = 0;
	while(position < 20){
		int steps = dice->waitAndPop();
		position = position + steps;
		printStatus(steps,position>=20);
		randomSleep();
	}
	winners->push(std::this_thread::get_id());
}


//Helper for sleeping
void randomSleep(){
	int time2Wait = std::rand()%3;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	std::this_thread::sleep_for(t);
}

//Print a Move
void printStatus(int spaces, bool finished){
	static std::mutex ioLock;
	std::lock_guard<std::mutex> lk(ioLock);
	//Print Move
	std::cout << "Thread "
		<< std::this_thread::get_id()
		<< " moved forward "
		<< spaces
		<< " spaces."
		<< std::endl;
	//Did they cross the finish line?
	if(!finished){return;}
	//Print finished
	std::cout <<"Thread "
		<< std::this_thread::get_id()
		<< " has crossed the finish line."
		<< std::endl;
}
