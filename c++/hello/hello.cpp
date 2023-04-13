#include <iostream>
// <thread> header must always be included
#include <thread>

void hello()
{
    std::cout << "Hello World\n";
}

int returnNum()
{
    int num = 5;
    return num;
}

int main()
{
    // all threads in c++ are launched with std::thread
    std::thread t(hello);
    t.join();
    std::cout << returnNum() << "\n";
}
