#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

/**
There are n passenger threads (min 10) and one car thread. 
The passengers repeatedly wait to take rides in the car, which holds C passengers
(default C = 4 and C < n). 

However, the car can go around the track only when it is full. 

The car takes T seconds to go around the track each time it fills up. 

After getting a ride, each passenger wanders around the amusement park for between 
0 and W seconds before returing to the roller coaster for another ride. 

The program ends when all threads have been on the roller coaster 4
times. 

If the number of threads that have not exited th park is less than C, the car may ran run
partially full.
*/

// Number of passenger threads (min 10)
const int numPassengers = 10;
// Maximum number of passengers the car can hold
const int C = 4;
// Time the car takes to go around the track (in seconds)
const int T = 1;
// Maximum time a passenger wanders around the park (in seconds)
const int W = 3;
// Number of rides each passenger takes before exiting the park
const int R = 4;

std::mutex m;
std::condition_variable cv;

// Number of passengers waiting for a ride
int waiting = 0;
// Number of passengers in the car
int in_car = 0;
// Number of rides each passenger has taken
int rides[numPassengers];

// Function that represents a passenger thread
void passenger(int id)
{
    while (true)
    {
        // Wait for a ride
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, []{ return in_car < C; });
        waiting++;
        cv.notify_one();
        lock.unlock();

        // Wander around the park
        std::this_thread::sleep_for(std::chrono::seconds(rand() % W + 1));

        // Return to the roller coaster
        lock.lock();
        waiting--;
        rides[id]++;

        // Check if the passenger has taken the specified number of rides
        if (rides[id] == R)
        {
            std::cout << "Passenger " << id << " has exited the park.\n";
            lock.unlock();
            break;
        }
        lock.unlock();
    }
}

// Function that represents the car thread
void car()
{
    while (true)
    {
        // Wait for the car to fill up
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, []{ return waiting >= C; });
        in_car += C;
        waiting -= C;
        cv.notify_one();
        lock.unlock();

        // Go around the track
        std::this_thread::sleep_for(std::chrono::seconds(T));

        // Empty the car
        lock.lock();
        in_car = 0;
        cv.notify_one();

        // Check if all passengers have exited the park
        bool done = true;
        for (int i = 0; i < numPassengers; i++)
        {
            if (rides[i] < R)
            {
                done = false;
                break;
            }
        }
        if (done)
        {
            std::cout << "All passengers have exited the park.\n";
            lock.unlock();
            break;
        }
        lock.unlock();
    }
}

int main()
{
    std::cout << "Amusement park simulation started.\n";

    // Create the passenger threads
    std::thread passengers[numPassengers];
    for (int i = 0; i < numPassengers; i++)
    {
        passengers[i] = std::thread(passenger, i);
    }

    // Create the car thread
    std::thread car_thread(car);

    // Wait for the passenger and car threads to finish
    for (int i = 0; i < numPassengers; i++)
    {
        passengers[i].join();
    }
    car_thread.join();

    std::cout << "Amusement park simulation ended.\n";

    return 0;
}