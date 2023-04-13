//Mark Boady
//Drexel University 2021

//Class for a thread safe queue
#ifndef _SAFE_QUEUE_H_
#define _SAFE_QUEUE_H_

#include <mutex>
#include <condition_variable>
#include <iostream>
template <class T>
class safeQueue {
	private:
		//A node to store values in
		struct node{
			T* value = nullptr;
			node* next = nullptr;
		};
		//Head Pointer
		node* head;
		//Tail Pointer
		node* tail;
		//Size of queue
		int size;
		//Locks for safety
		mutable std::mutex headMut;
		mutable std::mutex tailMut;
		std::condition_variable condVar;
	public:
		//Create an Empty Queue
		safeQueue();
		//This data structure cannot be copied
		safeQueue(const safeQueue& other)=delete;
		//This data structure cannot be assigned
		safeQueue& operator=(const safeQueue& other)=delete;
		//Push a new value on the queue
		void push(T v);
		//Wait for a value then pop
		T waitAndPop();
		//Try to assign and pop to result
		//Return true on success
		bool tryToPop(T &result);
		//What is the length of the queue
		int length();
		//Is the queue Empty
		bool empty();
	private:
		//What is the first value in the queue
		T front();
		//Add to the Queue
		void enqueue(T v);
		//Debug
		void printQueue();
		node* getTail(){
			std::unique_lock<std::mutex> tL(tailMut);
			return tail;
		}
};


//We don't need to protect the constructor
//It should be built before shared access
template <class T>
safeQueue<T>::safeQueue(){
	head = new node();
	tail = head;
	size = 0;
}

template <class T>
void safeQueue<T>::push(T v){
	//Add value
	enqueue(v);
	//Notify on waiting thread
	condVar.notify_one();
}

//Wait until data is available
//then pop it
template <class T>
T safeQueue<T>::waitAndPop(){
	//We need to know the old node
	node* oldHead;
	{//Get a lock on the head
		std::unique_lock<std::mutex> hL(headMut);
		//Wait for elements
		condVar.wait(hL,
			[&]{return head!=getTail();}
		);
		//Determine the current head
		oldHead = head;
		head = head->next;
		size=size-1;
	}//The Queue is safe release the lock
	T value = *(oldHead->value);
	//Delete the old head
	delete oldHead;
	//Reutrn value
	return value;
}

//This version doesn't wait
//if the queue is empty it returns false
//allowing the thread to continue doing
//something else
template <class T>
bool safeQueue<T>::tryToPop(T &result){
	node* oldHead;
	{//Lock Scope
	std::lock_guard<std::mutex> hL(headMut);
	if(head==getTail()){return false;}
	//Get the current head
	oldHead = head;
	head = head->next;
	size--;
	}//End of Scope
	//Get the value
	result = *(oldHead->value);
	//Delete old node
	delete oldHead;
	//return value
	return true;
}

//Ask the Size of the queue
template <class T>
int safeQueue<T>::length(){
	//Lock this entire method
    std::scoped_lock<std::mutex, std::mutex>
        lk(headMut, tailMut);
	return size;
}

//Check if the queue is empty
template <class T>
bool safeQueue<T>::empty(){
	//Lock this entire method
	std::scoped_lock<std::mutex, std::mutex>
        lk(headMut, tailMut);
	return head==tail;
}

//Private Methods from a classic queue
//These are protected by the public methods



//Get first value in the queue
template <class T>
T safeQueue<T>::front(){
	return *head->value;
}


//Add value to the queue
template <class T>
void safeQueue<T>::enqueue(T v){
	//Pointer to the value
	T* value = new T(v);
	//New Dummy Node
	node* newTail = new node();
	{//Lock the TAIL of the queue
		std::lock_guard<std::mutex> tL(tailMut);
		//Update the Dummy node
		tail->value = value;
		//Add new Dummy node
		tail->next = newTail;
		tail = newTail;
		size=size+1;
	}//End Lock
}

//Print for Debugging
template <class T>
void safeQueue<T>::printQueue(){
	std::scoped_lock sL(headMut, tailMut);
	//Print
	std::cout << "Queue -> ";
	node* ptr = head;
	while(ptr!=tail){
		std::cout <<
			*(ptr->value)
			<< " -> ";
		ptr=ptr->next;
	}
	std::cout << "END"
		<< std::endl;
}


#endif
