#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;
condition_variable condition_;
mutex mutex_;
bool flag = false;


void print_ping(int ping_pong_number)
{
    unique_lock<mutex> lock(mutex_);
    for (int i = 0; i < ping_pong_number; i++)
    {

        condition_.wait(lock,[]{ return flag?true:false;});
        cout<<"\n\033[1;32mPING\033[0m\n";
        flag = !flag;
        condition_.notify_one();
    }
}

void print_pong(int ping_pong_number)
{
    unique_lock<mutex> lock(mutex_);
    for (int i = 0; i < ping_pong_number; i++)
    {
        condition_.wait(lock,[]{ return !flag?true:false;});
        cout<<"\n\033[1;31mPONG\033[0m\n";
        flag = !flag;
        condition_.notify_one();
    }
}

int main()
{
    int ping_pong_number = 6;
    thread thread_1(print_ping, ping_pong_number);
    thread thread_2(print_pong, ping_pong_number);
    thread_1.join();
    thread_2.join();
    return 0;
}
