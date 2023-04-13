/**
 @file
 @author Mark Boady
 @date 2021-2022
 @section Description
 
 A leaderboard is used to track when each racer finishes the race.
 */
#ifndef _LEADER_BOARD_H_
#define _LEADER_BOARD_H_

#include <thread>
#include "semaphore.h"

/**
 The LeaderBoard records which order the threads finish in.
 */
class LeaderBoard{
private:
	int racers;/**< number of racers playing*/
	std::thread::id* results;/**< Array to store results of race*/
	int current;/**< position of next racer to finish*/
	semaphore* s;/**< Semaphore to protect the attributes*/
public:
	/**
	 Create a new Leader Board with given number of spaces
	 @param numRacers is the total number of racers playing
	 */
	LeaderBoard(int numRacers);
	/**
	 Free the class from memory
	 */
	~LeaderBoard();
	/**
	 Add a racer to the leaderboard. Position is determined automatically.
	 @param me is the ID of the thread that just finished
	 */
	void addRacer(std::thread::id me);
	/**
	 Determine if the race is finished
	 @return True if all racers have crossed the finish line
	 */
	bool raceFinished();
	/**
	 Find out which thread crossed the finish line in position i.
	 @param i is the position to check
	 @return The thread ID of the racer in that position
	 */
	std::thread::id getPlace(int i);
};

#endif
