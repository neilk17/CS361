#include <iostream>
template <class T>
class safeQueue {
private:
    // node
    struct node {
        T value;
        node* next;
    };
    // Head Pointer
    node* head;
    // Tail Pointer
    node* tail;
    // size of queue
    int size;
    mutable std::mutex mut;
    std::condition_variable condVar;

public:
    safeQueue();
    void push(T v);
    T waitAndPop();
    bool tryToPop(T &result);
    int length();
    bool empty();

private:
    T front();
    void dequeue();
    void enqueue(T v);
};

template <class T>
safeQueue<T>::safeQueue(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
void safeQueue<T>::push(T v){
    std::lock_guard<std::mutex> lk(mut);
    enqueue(v);
    condVar.notify_all();
}

template <class T>
T safeQueue<T>::waitAndPop(){
    std::unique_lock<std::mutex> lk(mut);
    condVar.wait(lk,
            [this]{return head!=nullptr;});
    T result = front();
    dequeue();
    return result;
}

template <class T>
bool safeQueue<T>::tryToPop(T &result){
    std::lock_guard<std::mutex> lk(mut);
    if(head==nullptr){
        return false;
    }
    result = front();
    dequeue();
    return true;
};

template <class T>
int safeQueue<T>::length(){
    std::lock_guard<std::mutex> lk(mut);
    return size;
};

template <class T>
bool safeQueue<T>::empty(){
    std::lock_guard<std::mutex> lk(mut);
    return head==nullptr;
};

template <class T>
T safeQueue<T>::front(){
    return head->value;
}

template <class T>
void safeQueue<T>::dequeue(){
    node* temp = head;
    if(head->next == nullptr){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    else {
        head = head->next;
        size = size - 1;
    }

    delete temp;
}

template <class T>
void safeQueue<T>::enqueue(T v){
    node* n = new node();
    n->value = v;
    n->next = nullptr;
    if(head == nullptr) {
        head = n;
        tail = n;
        size = 1;
    }
    else {
        tail->next = n;
        tail = n;
        size++;
    }
}
