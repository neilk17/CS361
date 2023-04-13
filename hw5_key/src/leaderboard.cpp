/**
 @file
 @author Mark Boady
 @date 2021-2022
 @section Description
 
 Implementation of the LeaderBoard Class.
 */
#include "leaderboard.h"

LeaderBoard::LeaderBoard(int numRacers){
	s = new semaphore(1);
	current = 0;
	racers = numRacers;
	results = new std::thread::id[racers];
}
LeaderBoard::~LeaderBoard(){
	delete s;
	delete results;
}
void LeaderBoard::addRacer(std::thread::id me){
	s->wait();
	results[current]=me;
	current++;
	s->signal();
}
bool LeaderBoard::raceFinished(){
	s->wait();
	bool temp = current==racers;
	s->signal();
	return temp;
}
std::thread::id LeaderBoard::getPlace(int i){
	return results[i];
}
