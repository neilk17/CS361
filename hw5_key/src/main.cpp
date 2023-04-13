/**
 @mainpage CS361 - Thread Race 2000
 @section Description
 
 This program simulates threads racing. It requires the programmer to make safe data structures or protect existing data structures.
 
 Make Commands:
 
	 make
 
 will build the executable.
 
	 make run
 
 will run the experiments.
 
	 make clean

will clear out the compiled code.
 
	make doc
 
will build the doxygen files.
 
*/


/**
 @file
 @author Mark Boady
 @date 2021-2022
 @section Description
 
 Answer key example for Thread Race 2000 Homework
 */
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include "semaphore.h"
#include "dicequeue.h"
#include "leaderboard.h"


/**
 Check that a given string contains a positive integer
 @param text is the string to examine
 @return true if the string is a positive integer
 */
bool checkPosInt(std::string text);
/**
 Sleep thread for a random length of time between 0 and 2 seconds
 */
void randomSleep();

/**
 Global Lock to Protect I/O
 */
std::mutex ioLock;
/**
 Print that a thread has started
 */
void startMessage();
/**
 Print that a thread has moved forward
 @param step is how far forward the thread moved
 */
void moveMessage(int step);
/**
 Print that a thread has crossed the finish line
 */
void stopMessage();

/**
 The Game Master thread rolls dice and adds them to a queue. It runs until the leader board is full.
 @param DQ is a safe queue to put the dice into
 @param LB is a safe leaderboard to record results
 */
void gameMaster(DiceQueue* DQ,LeaderBoard* LB);
/**
 The racer takes dice rolls until it has moved 20 spaces
 @param DQ is a safe queue to read dice from
 @param LB is a safe leaderboard to record when I cross the finish line
 */
void racer(DiceQueue* DQ,LeaderBoard* LB);

/**
 Create racers and game master. Simulate a game being played.
 @param argc must be 2
 @param argv contains the number of racers in argv[1]
 @return 0 on success and 1 on error
 */
int main(int argc, char** argv){
	//Initiate a random number generator
	std::srand(std::time(NULL));
	//Check Number of Racers Given
	if(argc!=2){
		std::cout << "Number of racers required." << std::endl;
		std::cout << argv[0] << " [numberOfRacers]" << std::endl;
		return 1;
	}
	//Get Number of Racers from Command Line
	std::string raceInput = std::string(argv[1]);
	//Make sure Number of Racers is a Positive Integer
	if(!checkPosInt(raceInput)){
		std::cout << "Number of racers was not an integer." << std::endl;
		return 2;
	}
	//Convert Number Racers to Integer
	int numRacers = std::stoi(raceInput);
	//Tell the User the race is starting
	std::cout << "Starting Race with "
			<< numRacers
			<< " threads." << std::endl;

	//---------Race Starts---------------

	//Queue to Store Dice
	DiceQueue* Q = new DiceQueue();
	//Class to track winners
	LeaderBoard* LB = new LeaderBoard(numRacers);
	
	//Manage all threads
	std::thread* myThreads = new std::thread[numRacers+1];
	
	//Start the Game Host
	myThreads[0] = std::thread(gameMaster, Q, LB);
	//Start up racers
	for(int i=1; i < numRacers+1; i++){
		myThreads[i] = std::thread(racer,Q,LB);
	}
	//Wait for them all to end
	for(int i=0; i < numRacers+1; i++){
		myThreads[i].join();
	}
	//Print the Rankings
	for(int i=0; i < numRacers; i++){
		std::thread::id person = LB->getPlace(i);
		std::cout << (i+1) << ": " << person << std::endl;
	}
	//Clean Up Shop
	delete[] myThreads;
	delete Q;
	delete LB;
	//Simulation is Finished
	return 0;
}
//Simulate the Game Master
void gameMaster(DiceQueue* DQ,LeaderBoard* LB)
{
	while(true){
		for(int i=1; i <= std::rand()%5; i++){
			int roll = std::rand()%6+1;
			DQ->addDice(roll);
		}
		if(LB->raceFinished()){break;}
		randomSleep();
	}
	return;
}
//Simulate one racer
void racer(DiceQueue* DQ,LeaderBoard* LB)
{
	startMessage();
	int myPosition=0;
	while(myPosition < 20){
		int myMove = DQ->getDice();
		moveMessage(myMove);
		myPosition=myPosition+myMove;
		randomSleep();
	}
	LB->addRacer(std::this_thread::get_id());
	return;
}
/*IO Stuff*/
//Print that the thread has started
void startMessage()
{
	std::lock_guard<std::mutex> lk(ioLock);
	std::cout << "Thread "
		<< std::this_thread::get_id()
		<< " has left the gate."
		<< std::endl;
}
//Print that the thread has moved
void moveMessage(int step){
	std::lock_guard<std::mutex> lk(ioLock);
	std::cout << "Thread "
		<< std::this_thread::get_id()
		<< " moved forward "
		<< step
		<< " spaces."
		<< std::endl;
}
//Print that the thread is done
void stopMessage(){
	std::lock_guard<std::mutex> lk(ioLock);
	std::cout << "Thread "
		<< std::this_thread::get_id()
		<< " has crossed the finish line."
		<< std::endl;
}
//Loop over the char and make sure
//they are all in rang 0-9
bool checkPosInt(std::string text){
	//No Characters
	if(text.length()==0){
		return false;
	}
	//Check all letters
	for(int i=0; i < text.length(); i++){
		if(text[i] < '0' || text[i] > '9'){
			return false;
		}
	}
	return true;
}
//Sleep between 0 and 2 seconds
void randomSleep(){
	int time2Wait = std::rand()%3;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	std::this_thread::sleep_for(t);
}
