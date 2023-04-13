//Mark Boady
//Drexel University 2021

//Race some cars!

#include <iostream>
#include <thread>
#include "safeQueue.h"
#include "race.h"

int main(int argv, char** argc){
	//Sanity Check on inputs
	if(argv!=2){
		std::cout << "Number of racers required."
			<< std::endl;
	}
	int temp =atoi(argc[1]);
	if(temp < 1){
		std::cout << "Not Enough racers." << std::endl;
	}

	int racers = temp;
	//Get ready
	std::cout << "Starting Race with "
		<< racers
		<< " threads."
		<< std::endl;
	//Make threads
	std::thread* T = new std::thread[racers+1];
	//Make two queues
	safeQueue<int>* dice = new safeQueue<int>();
	safeQueue<std::thread::id>* winners
		= new safeQueue<std::thread::id>();
	//Start the racers
	for(int i=0; i < racers; i++){
		T[i] = std::thread(racer,dice,winners);
	}
	T[racers] = std::thread(gameMaster,dice,winners,racers);
	//Join Everything
	for(int i=0; i < racers+1; i++){
		T[i].join();
	}
	//Print out the winners
	int position = 1;
	while(!winners->empty()){
		std::thread::id place;
		winners->tryToPop(place);
		std::cout << position
			<< ": "
			<< place
			<< std::endl;
		position++;
	}
	return 0;
}
