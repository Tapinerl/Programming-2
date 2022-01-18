#include <iostream>
using namespace std;

int main()
{
    int number;
    cout << "How many numbers would you like to have? ";
    cin >> number;

    int i = 1;
    while(i <= number)
    {
        cout << "\n" << i << endl;
        i++;
    }


    return 0;
}
