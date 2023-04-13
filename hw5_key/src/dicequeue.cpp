/**
 @file
 @author Mark Boady
 @date 2021-2022
 @section Description
 
 Implementation of the Dice Queue Class
*/
#include "dicequeue.h"

DiceQueue::DiceQueue(){
	dice = new std::queue<int>;
	items = new semaphore(0);
	lock = new semaphore(1);
}
DiceQueue::~DiceQueue(){
	delete dice;
	delete items;
	delete lock;
}
void DiceQueue::addDice(int d){
	lock->wait();
	dice->push(d);
	lock->signal();
	items->signal();
}
int DiceQueue::getDice(){
	items->wait();
	lock->wait();
	int temp = dice->front();
	dice->pop();
	lock->signal();
	return temp;
}
