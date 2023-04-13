//Mark Boady
//Rendezvous Puzzle Solution

//We have two threads and we want them to meet
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "semaphore.h"

//Mutex Lock for printing
std::mutex ioLock;

//Two Threads that need to meet up
void threadA(int shortName, semaphore* semA , semaphore* semB);
void threadB(int shortName, semaphore* semA , semaphore* semB);

//Print with a lock to avoid interleaving IO output
void statusPrint(int name, int value);

//Random Time to Wait between 0-2 seconds
std::chrono::seconds waitTime();

int main(int argv, char** argc){
	//Initiate a random number generator
    std::srand(std::time(NULL));
    
	//Make our semaphore
	//Just two Binary Semaphores
	semaphore* semA = new semaphore(0);
	semaphore* semB = new semaphore(0);

	//Make thread 1
	std::thread A(threadA, 1, semA, semB);
	//Make thread 2
	std::thread B(threadB, 2, semA, semB);
	
	//Join Both to Exit
	A.join();
	B.join();

	return 0;
}


//Print the status of a thread
void statusPrint(int name, int value)
{
	std::lock_guard<std::mutex> lk(ioLock);
	std::cout << "Thread " << name
		<< " is at " << value
		<< "."
		<< std::endl;
}

//Wait a random time to simulate hard work
std::chrono::seconds waitTime(){
	int time2Wait = std::rand()%3;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	return t;
}

/*
	Both these threads simulate doing a complex task
	by counting and sleeping random amounts.
	The sleep period simulate some computationally
	complex task.
 */

//Count by 2 to 200 with sleeps
//Then prints -10
void threadA(int shortName, semaphore* semA , semaphore* semB)
{
	for(int i=0; i < 200; i+=2)
	{
		if(i%10==0){
			statusPrint(shortName,i);
		}
		//Fall Asleep
		std::this_thread::sleep_for(waitTime());
	}
	//Rendezvous Solution (Thread A)
	semA->signal();
	semB->wait();
	//End the function Rendezvous before this
	statusPrint(shortName,-10);
}
//Count by 1 to 50 with sleeps
//Then prints -20
void threadB(int shortName, semaphore* semA , semaphore* semB)
{
	for(int i=0; i < 50; i+=1)
	{
		if(i%10==0){
			statusPrint(shortName,i);
		}
		//Fall Asleep
		std::this_thread::sleep_for(waitTime());
	}
	//Rendezvous Solution (Thread A)
	semB->signal();
	semA->wait();
	//End the function Rendezvous before this
	statusPrint(shortName,-20);
}
