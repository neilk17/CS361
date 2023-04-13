//Mark Boady
//Drexel University 2021

#include "philosopher.h"

philosopher::philosopher(int i, semaphore** myForkArray){
    myId = i;
    forks = myForkArray;
}

void philosopher::run(){
	for(int i=0; i < 2; i++){
		think();
		getForks();
		eat();
		putForks();
	}
}

//Think About Life
void philosopher::think(){
    display("I am thinking!");
    sleepRand(5);
    display("I am done thinking.");
}
//Eat some food
void philosopher::eat(){
	display("I am eating!");
	sleepRand(5);
    display("I am done eating.");
}

//Where is my left fork
int philosopher::left(){
	return myId;
}
//Where is my right fork
int philosopher::right(){
	return (myId+1)%5;
}

/* Version 1
//Just grab the forks and hope for the best
//deadlocks if we get very unlucky
//Get two forks
void philosopher::getForks(){
	forks[right()]->wait();
	display("Got Left Fork");
	forks[left()]->wait();
	display("Got Right Fork");
}
//Put down the forks
void philosopher::putForks(){
	forks[right()]->signal();
	display("Released Left Fork");
	forks[left()]->signal();
	display("Released Right Fork");
}
*/

//Version 2
//Some are lefty and some are righty
//Avoids Deadlock
//Get two forks
void philosopher::getForks(){
	if(myId%2==1){
		forks[right()]->wait();
		display("Got Left Fork");
		forks[left()]->wait();
		display("Got Right Fork");
	}else
	{
		forks[left()]->wait();
		display("Got Right Fork");
		forks[right()]->wait();
		display("Got Left Fork");
	}
}
//Put down the forks
void philosopher::putForks(){
	if(myId%2==1){
		forks[right()]->signal();
		display("Released Left Fork");
		forks[left()]->signal();
		display("Released Right Fork");
	}else{
		forks[left()]->signal();
		display("Released Right Fork");
		forks[right()]->signal();
		display("Released Left Fork");
	}
}


//Sleep for between 0 and maxTime
void philosopher::sleepRand(int maxTime){
    int time2Wait = std::rand()%(maxTime+1);
    std::chrono::seconds t
            = std::chrono::seconds(time2Wait);
    std::this_thread::sleep_for(t);
    return;
}
//Print Out with a lock
void philosopher::display(std::string text){
	static std::mutex ioLock;
	std::lock_guard<std::mutex> lk(ioLock);
    std::cout << "Philosopher "
        << myId
        << ": "
        << text
        << std::endl;
}
