#include <atomic>
#include <vector>
#include <iostream>
#include "safeQueue.h"

class threadPool
{
    std::atomic_bool done;
    thread_safe_queue<> work_queue;
};
