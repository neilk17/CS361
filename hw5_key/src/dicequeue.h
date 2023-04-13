/**
 @file
 @author Mark Boady
 @date 2021-2022
 @section Description
 
 The dice queue is used to send dice from the game master to the players. It uses a solution to the producer-consumer problem.
 */

#ifndef _DICE_QUEUE_H_
#define _DICE_QUEUE_H_

#include "semaphore.h"
#include <queue>

/**
 Implement a Queue using the Producer-Consumer Problem.
 */
class DiceQueue{
private:
	std::queue<int>* dice;/**< The actual queeu of dice*/
	semaphore* items;/**< Semaphore to signal consumers that the producer has produced.*/
	semaphore* lock;/**< Semaphore to protect the queue.*/
public:
	/**
	 Create a new empty Queue. Set up semaphores correctly.
	 */
	DiceQueue();
	/**
	 Delete all allocated objects.
	 */
	~DiceQueue();
	/**
		Add a dice roll to the queue when it is safe to do so.
	 @param d is the dice roll to add.
	 */
	void addDice(int d);
	/**
	 Get a dice roll or wait until one is available.
	 @return A roll of the dice
	 */
	int getDice();
};

#endif
