#include <iostream>

using namespace std;

int mult(int x, int y);

int main()
{
    int x, y;
    cout << "Enter 2 numbers to multiply: ";
    cin >> x >> y;
    cin.ignore();
    int ans = mult(x, y);
    cout << x << " * " << y << " = " << ans <<endl;
    cin.get();
} 

int mult(int x, int y)
{
    return x * y;
}
