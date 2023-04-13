//Mark Boady
//Drexel University 2021

//A queue of tasks

#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class taskQueue{
    private:
        std::queue<T>* data;
        bool closed;
        mutable std::mutex qLock;
        std::condition_variable condVar;
    public:
        //Create new Queue
        taskQueue();
        //Delete Class
        ~taskQueue();
        //Add a task
        void addTask(T value);
        //True on success False on
        //closed
        bool getTask(T &result);
        //Close Queue
        void close();
        
};

template <class T>
taskQueue<T>::taskQueue(){
    data = new std::queue<T>();
    closed=false;
}

template <class T>
taskQueue<T>::~taskQueue(){
    delete data;
}

template <class T>
void taskQueue<T>::addTask(T value){
    std::lock_guard<std::mutex> lk(qLock);
    if(closed){return;}
    data->push(value);
    condVar.notify_all();
}

template <class T>
bool taskQueue<T>::getTask(T &result){
    std::unique_lock<std::mutex> lk(qLock);
    condVar.wait(lk,
        [&]{return !data->empty() || closed;}
    );
    if(closed && data->empty()){return false;}
    T temp = data->front();
    data->pop();
    result = temp;
    return true;
}

template <class T>
void taskQueue<T>::close(){
    std::lock_guard<std::mutex> lk(qLock);
    closed=true;
    condVar.notify_all();
}

#endif

