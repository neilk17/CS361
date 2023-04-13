#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <chrono>

void getWeather(std::map<std::string, int> weatherMap) 
{
    while(true) {
        for(auto& item: weatherMap) {
            item.second++; // Increments the temperature
            std::cout << item.first << " " << item.second << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

}

int main()
{
    std::map<std::string, int> weatherMap = {
        {"Philadelphia",13},
        {"Mumbai",60},
        {"New York", 15}
    };

    std::thread bgWorker(getWeather, weatherMap);
}
