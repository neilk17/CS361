#include <iostream>

using namespace std;

int main()
{
    int *phonePointer;
    int phone;

    phonePointer = &phone;
    cin >> phone;
    cin.ignore();

    cout << phonePointer << "\n";
    cout << &phone << "\n";
    cout << phone << "\n";
    cin.get();
} 

